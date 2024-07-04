#include "../include/libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*
int main(void)
{
	int i;
	char str[] = "abcde1234}";
	i = 0;
	while (i < 10)
	{
		printf("%d\n", ft_isdigit(str[i]));
		i++;
	}
	return (0);
}
*/
