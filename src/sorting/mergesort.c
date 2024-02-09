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
	
	unsigned int	i = 1;
	t_file			*left = tree;
	t_file			*right = tree;
	t_file			*tmp;

	while (right && i < left->listsize / 2) {
		tmp = right;
		right = right->next;
		i++;
	}
	right->listsize = left->listsize - i;
	left->listsize = i;
	tmp = NULL;

	left = mergesortlist(left);
	right = mergesortlist(right);

	return merge(left, right);
}
