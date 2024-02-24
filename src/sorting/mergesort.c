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
		if (SORTDIR(left, right))
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
		if (SORTDIR(left, right))
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
	return new;
}

t_file	*splitList(t_file *head)
{
	t_file *fast = head;
	t_file *slow = head;
	t_file *prev = NULL;

	while (fast && fast->next) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	if (prev)
		prev->next = NULL;
	return slow;
}

t_file	*mergesortFileList(t_file *tree)
{
	if (tree == NULL || tree->next == NULL)
		return tree;

	t_file			*left = tree;
	t_file			*right = splitList(tree);

	left = mergesortFileList(left);
	right = mergesortFileList(right);

	return merge(left, right);
}
