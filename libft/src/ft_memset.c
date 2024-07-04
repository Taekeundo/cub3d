#include "../include/libft.h"

void	*ft_memset(void *dst, int val, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)dst)[i] = val;
		i++;
	}
	return (dst);
}

/*
int	main(void)
{
	char	*str;

	str = "abcedfg";
	printf("%s\n", (char *)ft_memset(str, 48, 3));
	return (0);
}
*/
