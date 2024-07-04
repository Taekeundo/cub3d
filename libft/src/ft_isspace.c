#include "../include/libft.h"

int	ft_isspace(char character)
{
	if (character == ' ' || character == '\t')
		return (1);
	return (0);
}