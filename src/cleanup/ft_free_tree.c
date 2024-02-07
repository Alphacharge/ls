#include "ft_ls.h"

void	ft_free_tree(t_file	*tree)
{
	t_file	*tmp;
	while (tree) {
		tmp = tree;
		if (tree->sub)
			ft_free_tree(tree->sub);
		tree = tree->next;
		ft_free(tmp);
		tmp = NULL;
	}
}
