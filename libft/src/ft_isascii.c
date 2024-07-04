#include "../include/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
int	main(void)
{
	int		i;
	char	*str;

	str[] = "abcde//€34}";
	i = 0;
	while (i < 10)
	{
		printf("%d\n", ft_isascii(str[i]));
		i++;
	}
	return (0);
}
*/
