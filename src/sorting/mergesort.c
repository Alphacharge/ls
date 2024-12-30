#include "ft_ls.h"

/**
 * Merges two sorted linked lists of t_file structures based on the sorting criteria specified by SORTDIR macro.
 * @param left - Pointer to the head of the first sorted linked list to be merged.
 * @param right - Pointer to the head of the second sorted linked list to be merged.
 * @return Pointer to the head of the merged sorted linked list.
 */
// #include "mpsort.h"
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

/**
 * Splits a linked list into two halves using the slow-fast pointer technique.
 * @param head - Pointer to the head of the linked list to be split.
 * @return Pointer to the head of the second half of the split linked list.
 */
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

/**
 * Sorts a linked list of t_file structures using the merge sort algorithm.
 * @param tree - Pointer to the head of the linked list to be sorted.
 * @return Pointer to the head of the sorted linked list.
 */
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
