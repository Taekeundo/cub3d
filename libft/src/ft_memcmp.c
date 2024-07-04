#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (i < n)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = "abc12";
	str2 = "abc42";
	printf("str1: %s\n", str1);
	printf("str2: %s\n", str2);
	printf("\n");
	printf("orginal cmp: %d\n", memcmp(str1, str2, 5));
	printf("result of cmp: %d\n", ft_memcmp(str1, str2, 5));
	return (0);
}
*/
