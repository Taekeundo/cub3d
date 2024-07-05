
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:03:18 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 16:38:41 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_char_array(char **array)
{
	int	count;

	if (array == NULL)
		return (1);
	count = -1;
	while ((array)[++count])
		free((array)[count]);
	free(array);
	return (1);
}
