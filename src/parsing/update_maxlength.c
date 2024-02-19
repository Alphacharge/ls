#include "ft_ls.h"

void	update_maxlength(t_file *head, unsigned int length)
{
	t_file	*tmp = head;

	while (tmp)
	{
		tmp->maxlength = length;
		tmp = tmp->next;
	}
}
