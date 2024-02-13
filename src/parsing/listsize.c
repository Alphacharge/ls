#include "ft_ls.h"

unsigned int	listsize(t_file *tree)
{
	if (!tree)
		return 0;
	unsigned int i = 0;
	while (tree) {
		tree = tree->next;
		i++;
	}
	return i;
}
