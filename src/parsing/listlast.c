#include "ft_ls.h"

t_file	*listlast(t_file *tree)
{
	while (tree && tree->next)
		tree = tree->next;
	return tree;
}
