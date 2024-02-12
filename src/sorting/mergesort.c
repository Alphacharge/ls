#include "ft_ls.h"

t_file	*merge(t_file *left, t_file *right)
{
	if (left && !right)
		return left;
	else if (!left && right)
		return right;
	else if (!left && !right)
		return NULL;
	
	char	*pair[3];
	pair[0] = left->name;
	pair[1] = right->name;
	pair[2] = NULL;
	bubblesort(pair, 2, F_ISSET(*(left->data->flags), F_REVERSE));
	if (!ft_strcmp(pair[0], left->name)){
		left->next = right;
		left->listsize++;
		return left;
	} else {
		right->next = left;
		right->listsize++;
		return right;
	}

}

t_file	*mergesortlist(t_file *tree)
{
	if (tree == NULL || tree->next == NULL)
		return tree;
	
	unsigned int	midpoint = tree->listsize / 2;
	unsigned int	counter = 0;
	t_file			*left = tree;
	t_file			*right = tree;

	while (right && right->next && counter < midpoint) {
		right = right->next;
		counter++;
	}
	ft_printf("lstsize:%d\tmidpoint:%d\tcounter:%d\n", tree->listsize, midpoint, counter);
	ft_printf("tree:\t%p\nleft:\t%p\nright:\t%p\n", tree, left, right);
	return NULL;
	// unsigned int	midpoint = tree->listsize / 2;
	// unsigned int 	i = 0;
	// t_file			*left = tree;
	// t_file			*right = tree;
	// t_file			*tmp = NULL;
	// for (; right && i < midpoint; i++) {
	// 	right = right->next;
	// }
	// tmp = right;
	// right = right->next;
	// left->listsize = i;
	// right->listsize = tree->listsize - i;
	// tmp->next = NULL;

	// left = mergesortlist(left);
	// right = mergesortlist(right);

	// return merge(left, right);
}
