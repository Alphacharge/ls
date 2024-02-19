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
	new->listsize = listsize(new);
	// ft_printf("Merged Tree: size:(%d)\n", listsize(new));
	// print_inline_tree(new);
	return new;
}

t_file	*splitlist(t_file *head)
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
	head->listsize = listsize(head);
	slow->listsize = listsize(slow);
	return slow;
}

t_file	*mergesortlist(t_file *tree)
{
	if (tree == NULL || tree->next == NULL)
		return tree;

	// ft_printf("in merge lstsize: %d\n", listsize(tree));

	t_file			*left = tree;
	t_file			*right = splitlist(tree);

	// ft_printf("sizeleft:\t%d\n",listsize(left));
	// ft_printf("sizeright:\t%d\n",listsize(right));
	// ft_printf("Tree Left:\n");
	// print_inline_tree(left);
	// ft_printf("Tree Right:\n");
	// print_inline_tree(right);
	// ft_printf("-----------------\n");
	// left->listsize = listsize(left);
	// right->listsize = listsize(right);

	left = mergesortlist(left);
	right = mergesortlist(right);

	return merge(left, right);
}
