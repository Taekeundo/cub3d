#include "../include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

/*
*lst means just Head.
	1. Find exceptions and handlig.
	2. Link new with lst // (new) point (lst's head)
	3. Change start point // Currently (lst's head) is (New)
*/
