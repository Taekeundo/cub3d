#include "../include/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
int	main(void)
{
	const char	*str;

	str = "abcde";
	printf("%zu\n", ft_strlen(str));
	return (0);
}
*/
