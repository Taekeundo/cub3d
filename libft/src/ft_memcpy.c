#include "../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (dst);
	while (i < len)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	char	dst[] = "ABCDEFGHI";
	char	src[] = "123456789";

	printf("dst: %s\n", dst);
	printf("src: %s\n", src);
	ft_memcpy(dst, src, 9);
	printf("after: %s\n", dst);
	return (0);
}
*/
