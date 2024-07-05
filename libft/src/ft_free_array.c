/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:18:51 by tkwak             #+#    #+#             */
/*   Updated: 2023/06/22 12:09:02 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
