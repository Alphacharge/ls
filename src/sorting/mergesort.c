#include "ft_ls.h"

t_file	*merge(t_file *left, t_file *right)
{
	t_file	*new = NULL;
	t_file	*tmp = NULL;

	if (left && !right)
		new = left;
	else if (!left && right)
		new = right;
	else 
	{
		if (ft_strcmp(left->name, right->name) < 0)
		{
			new = left;
			left = left->next;
		}
		else
		{
			new = right;
			right = right->next;
		}
	}
	tmp = new;
	while (left && right)
	{
		if (ft_strcmp(left->name, right->name) < 0)
		{
			tmp->next = left;
			left = left->next;
		}
		else
		{
			tmp->next = right;
			right = right->next;
		}
		tmp = tmp->next;
	}
	if (left)
		tmp->next = left;
	else if (right)
		tmp->next = right;
	new->listsize = listsize(new);
	return new;
}

t_file	*mergesortlist(t_file *tree)
{
	if (tree == NULL || tree->next == NULL)
		return tree;
	
	unsigned int	midpoint = tree->listsize / 2;
	unsigned int 	i = 0;
	t_file			*left = tree;
	t_file			*right = tree;
	t_file			*tmp = NULL;
	while (right && i < midpoint) {
		tmp = right;
		right = right->next;
		i++;
	}
	tmp->next = NULL;
	left->listsize = listsize(left);
	right->listsize = listsize(right);

	left = mergesortlist(left);
	right = mergesortlist(right);

	return merge(left, right);
}
