#include "ft_ls.h"

void	ft_free_tree(t_file	*tree)
{
	t_file	*tmp;
	while (tree) {
		tmp = tree;
		ft_free((void**)&tree->fullpath_name);
		ft_free((void**)&(tree->name));
		tree = tree->next;
		ft_free((void**)&(tmp));
	}
}
