#include "../include/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*
int	main(void)
{
	int		i;
	char	*str;

	str[] = "abced\n\r\t\bd";
	i = 0;
	while (i < 10)
	{
		printf("%d\n", ft_isprint(str[i]));
		i++;
	}
	return (0);
}
*/
