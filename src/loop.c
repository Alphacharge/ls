#include "ft_ls.h"

void	loop(t_data **data, t_file **treelvl, char *path, DIR *ref)
{
	//print stuff and generate child if recursive
	if (treelvl != NULL)
	{
		*treelvl = mergesortlist(*treelvl);
		print_treelvl(treelvl);
		//if recursive generate child tree
		if (F_ISSET((*(*data)->flags), F_RECURSIVE))
		{
			t_file *current = *treelvl;
			while (current)
			{
				if (!isSpecialDir(current->name) && (!isDotfile(current->name) || (isDotfile(current->name) && F_ISSET(*(*data)->flags, F_ALL))) && current->type == _DIR)
				{
					DIR	*dir = opendir(current->fullpath_name);
					if (dir == NULL) {
						perror(current->fullpath_name);
						current = current->next;
						continue;
					}
					ft_printf("\n%s:\n", current->fullpath_name);
					loop(data, NULL, current->fullpath_name, dir);
				}
				current = current->next;
			}
		}
		ft_free_tree(*treelvl);
	}
	//if nothing to print, then generate something
	else
	{
		if (ref == NULL)
			ft_error(*data, 6);
		struct dirent *dir = readdir(ref);
		t_file	*head = NULL;
		while (dir != NULL) {
			if (isDotfile(dir->d_name) && !F_ISSET((*(*data)->flags), F_ALL)){
				dir = readdir(ref);
				continue;
			}
			t_file	*new = listNew(*data);
			if (new == NULL)
				ft_error(*data, 3);
			setFileType(new, dir->d_type);
			new->name = ft_strdup(dir->d_name);
			new->path = path;
			new->fullpath_name = ft_multijoin(false, 3, path, "/", dir->d_name);
			new->length = NAMELENGTH;
			if (new->name == NULL || new->fullpath_name == NULL)
				ft_error(*data, 5);
			if ((F_ISSET(*new->data->flags, F_LONG) || F_ISSET(*new->data->flags, F_MTIME)) && lstat(new->fullpath_name, &new->stat) < 0)
				ft_error(*data, 4);
			dir = readdir(ref);
			if (head == NULL)
				head = new;
			else
			{
				t_file	*last = head;
				while (last && last->next){
					if (last->length < new->length)
						last->length = new->length;
					last = last->next;
				}
				last->next = new;
			}
			head->listsize = listSize(head);
		}
		if (ref)
			closedir(ref);
		//call recursive to print
		if (head != NULL)
			loop(data, &head, head->fullpath_name, NULL);
	}
}
