#include "ft_ls.h"

void	listUpdateMaxlength(t_file *head, unsigned int length)
{
	t_file	*tmp = head;

	while (tmp)
	{
		tmp->maxlength = length;
		tmp = tmp->next;
	}
}
