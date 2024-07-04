#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}
/*
int main(void)
{
	char *p = "abced";

	printf("%s\n", p);
	p = calloc(3, 1);
	printf("%s\n", p);
	return (0);
}
*/
