#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*res;

	if (s1 && s2)
	{
		len1 = strlen(s1);
		len2 = strlen(s2);
		res = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (res == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			res[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			res[len1] = s2[i];
			len1++;
		}
		res[len1] = '\0';
		return (res);
	}
	return (NULL);
}
*/
