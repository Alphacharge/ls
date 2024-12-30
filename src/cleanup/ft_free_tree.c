#include "ft_ls.h"

/**
 * Recursively frees the memory allocated for a linked list of t_file structures,
 * including their associated strings (fullPathName, fileName, userName, groupName).
 * @param tree - Pointer to the head of the linked list of t_file structures to be freed.
 */
void	ft_free_tree(t_file	*tree)
{
	t_file	*tmp;
	while (tree) {
		tmp = tree;
		ft_free((void**)&tree->fullPathName);
		ft_free((void**)&(tree->fileName));
		ft_free((void**)&tree->lowercaseName);
		ft_free((void**)&(tree->userName));
		ft_free((void**)&(tree->groupName));
		tree = tree->next;
		ft_free((void**)&(tmp));
	}
}
