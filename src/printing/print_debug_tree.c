#include "ft_ls.h"

// void	print_debug_tree(t_file *tree, int lvl)
// {
// 	ft_printf("Listsize tree:%d\n", listSize(tree));
// 	// int		intend = 0;
// 	while (tree != NULL && tree->next != NULL)
// 	{
// 		// while (intend++ < lvl)
// 		// 	ft_printf("-");
// 		ft_printf("lvl:%d\tname:%s\tsize:%d\ttype:%d\n", lvl, tree->fullpath_name, tree->listsize, tree->type);
// 		if (tree->type == _DIR && tree->sub)
// 			print_debug_tree(tree->sub, lvl + 1);
// 		tree = tree->next;
// 	}
// }
