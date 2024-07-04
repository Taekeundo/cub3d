#include "../include/libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] && ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	if (str[i] && ((str[i] == '-') || (str[i] == '+')))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
