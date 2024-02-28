#include "ft_ls.h"

void	ft_free_tree(t_file	*tree)
{
	t_file	*tmp;
	while (tree) {
		tmp = tree;
		ft_free((void**)&tree->fullPathName);
		ft_free((void**)&(tree->fileName));
		ft_free((void**)&(tree->userName));
		ft_free((void**)&(tree->groupName));
		tree = tree->next;
		ft_free((void**)&(tmp));
	}
}
