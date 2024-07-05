
#include "../include/libft.h"

int	free_char_array(char **array)
{
	int	count;

	if (array == NULL)
		return ;
	count = -1;
	while ((array)[++count])
		free((array)[count]);
	free(array);
	return (1);
}
