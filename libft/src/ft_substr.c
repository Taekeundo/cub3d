#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	index;

	index = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	while (index < len && s[start + index] != '\0')
	{
		tmp[index] = s[start + index];
		index++;
	}
	tmp[index] = '\0';
	return (tmp);
}
