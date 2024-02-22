#include "ft_ls.h"

unsigned int	listSize(t_file *tree)
{
	if (!tree)
		return 0;
	unsigned int i = 0;
	const t_file *current = tree;
	while (current) {
		current = current->next;
		i++;
	}
	return i;
}
