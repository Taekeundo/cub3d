#include "../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (unsigned char)c && (unsigned char)c != '\0')
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (0);
}

/*
int	main(void)
{
	char	*str;

	str = "dasdasdhknpvbono";
	printf("%s\n", ft_strchr(str, 0));
	return (0);
}
*/
// Variable (const char*) can't be changed.
// If we get a return value related with const char *str
//  we have to cast that value to normal (char *str) for modify.
// Reason, using unsinged char:
// Certain environment of CPU-Architecture, unsigned char is default.
