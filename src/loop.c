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
			new->maxFileNameLength = new->fileNameLength;
			if (new->fileName == NULL || new->fullPathName == NULL)
				ft_error(*data, 5);
			if ((F_ISSET(*new->data->flags, F_LONG) || F_ISSET(*new->data->flags, F_MTIME)) && lstat(new->fullPathName, &new->stat) < 0)
				ft_error(*data, 4);
			if (F_ISSET(*new->data->flags, F_LONG)) {
				new->pwd = getpwuid(new->stat.st_uid);
				if (new->pwd == NULL)
					ft_error(*data, 4);
				new->grp = getgrgid(new->stat.st_gid);
				if (new->grp == NULL)
					ft_error(*data, 4);
				new->userLength = ft_strlen(new->pwd->pw_name);
				new->maxUserLength = new->userLength;
				new
				new->groupLength = ft_strlen(new->grp->gr_name);
				new->maxGroupLength = new->groupLength;
				new->maxLinks = new->stat.st_nlink;
				new->maxBytes = new->stat.st_size;
				new->totalBlocks = new->stat.st_blocks;
			}
			dir = readdir(ref);
			if (head == NULL)
				head = new;
			else
			{
				t_file	*last = head;
				while (last && last->next){
					if (last->maxFileNameLength < new->fileNameLength)
						last->maxFileNameLength = new->fileNameLength;
					if (F_ISSET(*new->data->flags, F_LONG)) {
						if (last->maxLinks < new->stat.st_nlink)
							last->maxLinks = new->stat.st_nlink;
						if (last->maxBytes < new->stat.st_size)
							last->maxBytes = new->stat.st_size;
						if (last->maxUserLength < new->userLength)
							last->maxUserLength = new->userLength;
						if (last->maxGroupLength < new->groupLength)
							last->maxGroupLength = new->groupLength;
						last->totalBlocks += new->totalBlocks;
					}
					// ft_printf("->%s,\t\t%d,\t\t%d\n", last->fileName, last->maxFileNameLength, last->maxLinks);
					last = last->next;
				}
				if (last->maxFileNameLength < new->maxFileNameLength)
					last->maxFileNameLength = new->maxFileNameLength;
				if (F_ISSET(*new->data->flags, F_LONG)) {
					if (last->maxLinks < new->stat.st_nlink)
						last->maxLinks = new->stat.st_nlink;
					if (last->maxBytes < new->stat.st_size)
						last->maxBytes = new->stat.st_size;
					if (last->maxUserLength < new->userLength)
						last->maxUserLength = new->userLength;
					if (last->maxGroupLength < new->groupLength)
						last->maxGroupLength = new->groupLength;
					last->totalBlocks += new->totalBlocks;
				}
				new->maxFileNameLength = last->fileNameLength;
				new->maxLinks = last->maxLinks;
				new->maxBytes = last->maxBytes;
				new->totalBlocks = last->totalBlocks;
				new->maxUserLength = last->maxUserLength;
				new->maxGroupLength = last->maxGroupLength;
					// ft_printf("->->%s,\t\t%d,\t\t%d\n", last->fileName, last->maxFileNameLength, last->maxLinks);
					// ft_printf("-------------------------------------\n");
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
