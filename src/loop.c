#include "ft_ls.h"

void	loop(t_data *data, t_file *treelvl, char *path, DIR *ref)
{
	if (treelvl != NULL)
	{
// ft_printf("1\tlistsize:%d\n", treelvl->listsize);
// print_inline_tree(treelvl);
		treelvl = mergesortlist(treelvl);
// print_inline_tree(treelvl);
		print_treelvl(treelvl);
		if (ref)
			closedir(ref);
		if (F_ISSET(*(data->flags), F_RECURSIVE))
		{
			t_file *current = treelvl;
			while (current)
			{
				if (!is_special_dir(current->name) && current->type == _DIR)
				{
					DIR	*dir = opendir(current->fullpath_name);
					if (dir == NULL) {
						perror(current->fullpath_name);
						break;
					}
					loop(data, NULL, current->fullpath_name, dir);
				}
				current = current->next;
			}
		}
		ft_free_tree(treelvl);
	}
	else
	{
		if (ref == NULL)
			ft_error(data, 6);
// ft_printf("2\n");
		struct dirent *dir = readdir(ref);
		t_file	*head = NULL;
		while (dir != NULL) {
// ft_printf("3\n");
			t_file	*new = new_node(data);
			if (new == NULL)
				ft_error(data, 3);
			if (head == NULL)
				head = new;
			else
			{
				t_file	*last = head;
				while (last && last->next)
					last = last->next;
				last->next = new;
			}
			set_file_type(new, dir->d_type);
			new->name = ft_strdup(dir->d_name);
			new->path = path;
			new->fullpath_name = ft_multijoin(false, 3, path, "/", dir->d_name);
			new->length = NAMELENGTH;
			if (new->length > head->maxlength)
				update_maxlength(head, new->length);
			if (new->name == NULL || new->fullpath_name == NULL)
				ft_error(data, 5);
			if ((F_ISSET(*new->data->flags, F_LONG) || F_ISSET(*new->data->flags, F_MTIME)) && lstat(new->fullpath_name, &new->stat) < 0)
				ft_error(data, 4);
			dir = readdir(ref);
			head->listsize = listsize(head);
		}
		loop(data, head, head->fullpath_name, NULL);

		// ft_printf("lstsize: %d\n", listsize(head));
	}
}
