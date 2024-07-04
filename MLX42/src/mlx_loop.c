#include "MLX42/MLX42_Int.h"

//= Private =//

static void	mlx_exec_loop_hooks(mlx_t*	mlx)
{
	const mlx_ctx_t* mlxctx = mlx->context;

	mlx_list_t*	lstcpy = mlxctx->hooks;
	while (lstcpy && !glfwWindowShouldClose(mlx->window))
	{
		mlx_hook_t* hook = ((mlx_hook_t*)lstcpy->content);
		hook->func(hook->param);
		lstcpy = lstcpy->next;
	}
}

static void mlx_render_images(mlx_t* mlx)
{
	mlx_ctx_t* mlxctx = mlx->context;
	mlx_list_t* imglst = mlxctx->images;

	if (sort_queue)
	{
		sort_queue = false;
		mlx_sort_renderqueue(&mlxctx->render_queue);
	}

	// Upload image textures to GPU
	while (imglst)
	{
		mlx_image_t* image;
		if (!(image = imglst->content)) {
			mlx_error(MLX_INVIMG);
			return;
		}

		glBindTexture(GL_TEXTURE_2D, ((mlx_image_ctx_t*)image->context)->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		imglst = imglst->next;
	}

	// Execute draw calls
	mlx_list_t* render_queue = mlxctx->render_queue;
	while (render_queue)
	{
		draw_queue_t* drawcall = render_queue->content;
		mlx_instance_t* instance =  &drawcall->image->instances[drawcall->instanceid];

		if (drawcall && drawcall->image->enabled && instance->enabled)
			mlx_draw_instance(mlx->context, drawcall->image, instance);
		render_queue = render_queue->next;
	}
}

/**
 * @brief Adds a new function to be called in the main loop.
 * This function registers a new hook that will be called during each iteration of the main loop.
 *
 * @param mlx A pointer to the MLX context.
 * @param f A pointer to the function to be called during each iteration of the main loop.
 * @param param A pointer to the parameters that will be passed to the function.
 *
 * @return Returns true on success, or false on memory allocation failure.
 *
 * @note The function pointer @p f and the MLX context @p mlx must not be NULL.
 *
 * @details The function performs the following steps:
 *  - Validates the non-nullness of the parameters.
 *  - Allocates memory for a new hook.
 *  - Allocates memory for a new list node.
 *  - Assigns the function pointer and parameters to the new hook.
 *  - Adds the new hook to the list of hooks in the MLX context.
 *  - Returns true on successful addition, or false on memory allocation failure.
 */

bool mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(f);

	mlx_hook_t* hook;
	if (!(hook = malloc(sizeof(mlx_hook_t))))
		return (mlx_error(MLX_MEMFAIL));

	mlx_list_t* lst;
	if (!(lst = mlx_lstnew(hook)))
	{
		free(hook);
		return (mlx_error(MLX_MEMFAIL));
	}
	hook->func = f;
	hook->param = param;
	const mlx_ctx_t	*mlxctx = mlx->context;
	mlx_lstadd_back((mlx_list_t**)(&mlxctx->hooks), lst);
	return (true);
}
/**
 * @brief This is the main loop for the MLX application.
 * This function runs the main loop of the MLX application, handling rendering and event polling.
 *
 * @param mlx A pointer to the MLX context.
 *
 * @note The MLX context pointer @p mlx must not be NULL.
 *
 * @details The function performs the following steps:
 *  - Validates the non-nullness of the MLX context pointer.
 *  - Enters a loop that continues until the window is closed.
 *  - Calculates the time difference between frames and updates the delta time in the MLX context.
 *  - Clears the screen with a specific color.
 *  - Retrieves the current window size and updates the MLX context.
 *  - If the window size is greater than 1x1, updates the transformation matrix.
 *  - Executes any registered loop hooks.
 *  - Renders images and flushes the rendering batch.
 *  - Swaps the front and back buffers.
 *  - Polls for and processes events.
 */
void mlx_loop(mlx_t* mlx)
{
	MLX_NONNULL(mlx);

	double start, oldstart = 0;
	while (!glfwWindowShouldClose(mlx->window))
	{
		start = glfwGetTime();
		mlx->delta_time = start - oldstart;
		oldstart = start;
	
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetWindowSize(mlx->window, &(mlx->width), &(mlx->height));

		if ((mlx->width > 1 || mlx->height > 1))
			mlx_update_matrix(mlx);

		mlx_exec_loop_hooks(mlx);
		mlx_render_images(mlx);
		mlx_flush_batch(mlx->context);

		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
