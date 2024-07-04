#include "../include/libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*
int	main(void)
{
	int	a;

	a = 'B';
	printf("%d\n", ft_tolower(a));
	return (0);
}
*/
