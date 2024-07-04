#include "../include/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (fd < 0)
		return ;
	while (s[index] != '\0')
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
	write(fd, "\n", 1);
}
