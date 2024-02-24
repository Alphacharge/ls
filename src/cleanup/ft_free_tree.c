#include "ft_ls.h"

void	ft_free_tree(t_file	*tree)
{
	t_file	*tmp;
	while (tree) {
		tmp = tree;
		ft_free((void**)&tree->fullPathName);
		ft_free((void**)&(tree->fileName));
		tree = tree->next;
		ft_free((void**)&(tmp));
	}
}
