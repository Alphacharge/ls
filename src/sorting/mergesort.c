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
	new->listsize = listSize(new);
	// ft_printf("Merged Tree: size:(%d)\n", listSize(new));
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
	head->listsize = listSize(head);
	slow->listsize = listSize(slow);
	return slow;
}

t_file	*mergesortlist(t_file *tree)
{
	if (tree == NULL || tree->next == NULL)
		return tree;

	// ft_printf("in merge lstsize: %d\n", listSize(tree));

	t_file			*left = tree;
	t_file			*right = splitlist(tree);

	// ft_printf("sizeleft:\t%d\n",listSize(left));
	// ft_printf("sizeright:\t%d\n",listSize(right));
	// ft_printf("Tree Left:\n");
	// print_inline_tree(left);
	// ft_printf("Tree Right:\n");
	// print_inline_tree(right);
	// ft_printf("-----------------\n");
	// left->listsize = listSize(left);
	// right->listsize = listSize(right);

	left = mergesortlist(left);
	right = mergesortlist(right);

	return merge(left, right);
}
