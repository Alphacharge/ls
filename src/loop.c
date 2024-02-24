#include "ft_ls.h"

void	loop(t_data **data, t_file **treelvl, char *path, DIR *ref)
{
	//print stuff and generate child if recursive
	if (treelvl != NULL)
	{
		*treelvl = mergesortFileList(*treelvl);
		if (F_ISSET((*(*data)->flags), F_LONG))
			printLongTreelvl(treelvl);
		else
			printTreelvl(treelvl);
		//if recursive generate child tree
		if (F_ISSET((*(*data)->flags), F_RECURSIVE))
		{
			t_file *current = *treelvl;
			while (current)
			{
				if (!isSpecialDir(current->fileName) && (!isDotfile(current->fileName) || (isDotfile(current->fileName) && F_ISSET(*(*data)->flags, F_ALL))) && current->fileType == _DIR)
				{
					DIR	*dir = opendir(current->fullPathName);
					if (dir == NULL) {
						perror(current->fullPathName);
						current = current->next;
						continue;
					}
					ft_printf("\n%s:\n", current->fullPathName);
					loop(data, NULL, current->fullPathName, dir);
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
			return ;
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
			new->fileName = ft_strdup(dir->d_name);
			// new->path = path;
			new->fullPathName = ft_multijoin(false, 3, path, "/", dir->d_name);
			new->fileNameLength = NAMELENGTH;
			if (new->fileName == NULL || new->fullPathName == NULL)
				ft_error(*data, 5);
			if ((F_ISSET(*new->data->flags, F_LONG) || F_ISSET(*new->data->flags, F_MTIME)) && lstat(new->fullPathName, &new->stat) < 0)
				ft_error(*data, 4);
			dir = readdir(ref);
			if (head == NULL)
				head = new;
			else
			{
				t_file	*last = head;
				while (last && last->next){
					if (last->fileNameLength < new->fileNameLength)
						last->fileNameLength = new->fileNameLength;
					last = last->next;
				}
				last->next = new;
			}
			// head->listsize = listSize(head);
		}
		if (ref)
			closedir(ref);
		//call recursive to print
		if (head != NULL)
			loop(data, &head, head->fullPathName, NULL);
	}
}
