#include "../include/libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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
