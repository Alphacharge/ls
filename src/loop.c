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
		if (errno != 0) {
			perror("readdir");
			closedir(ref);
		}
		t_file	*head = NULL;
		while (dir != NULL) {
			if (isDotfile(dir->d_name) && !F_ISSET((*(*data)->flags), F_ALL)){
				dir = readdir(ref);
				if (errno != 0)
					perror(NULL);
				continue;
			}
			t_file	*new = listNew(*data);
			if (new == NULL)
				ft_error(*data, 1);
			setFileType(new, dir->d_type);
			new->fileName = ft_strdup(dir->d_name);
			if (new->fileName == NULL){
				ft_putstr_fd("file name malloc error\n", 2);
				ft_error(*data, 1);
			}
			new->fullPathName = ft_multijoin(false, 3, path, "/", dir->d_name);
			if (new->fullPathName == NULL){
				ft_putstr_fd("path malloc error\n", 2);
				ft_error(*data, 1);
			}
			new->fileNameLength = NAMELENGTH;
			new->maxFileNameLength = new->fileNameLength;
			if ((F_ISSET(*new->data->flags, F_LONG) || F_ISSET(*new->data->flags, F_MTIME)) && lstat(new->fullPathName, &new->stat) < 0){
				perror("lstat");
				ft_error(*data, 1);
			}
			if (F_ISSET(*new->data->flags, F_LONG)) {
				struct passwd	*pwd;
				struct group	*grp;
				pwd = getpwuid(new->stat.st_uid);
				if (pwd == NULL)
					ft_error(*data, 4);
				grp = getgrgid(new->stat.st_gid);
				if (grp == NULL)
					ft_error(*data, 4);
				new->userLength = ft_strlen(pwd->pw_name);
				new->maxUserLength = new->userLength;
				new->userName = ft_strdup(pwd->pw_name);
				if (new->userName == NULL){
					ft_putstr_fd("user malloc error\n", 2);
					ft_error(*data, 1);
				}
				new->groupLength = ft_strlen(grp->gr_name);
				new->maxGroupLength = new->groupLength;
				new->groupName = ft_strdup(grp->gr_name);
				if (new->groupName == NULL){
					ft_putstr_fd("group malloc error\n", 2);
					ft_error(*data, 1);
				}
				new->maxLinks = new->stat.st_nlink;
				new->maxBytes = new->stat.st_size;
				new->totalBlocks = new->stat.st_blocks;
			}
			dir = readdir(ref);
			if (errno != 0) {
				perror("readdir");
				closedir(ref);
			}
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
				last->next = new;
			}
		}
		if (ref)
			closedir(ref);
		if (head != NULL)
			loop(data, &head, head->fullPathName, NULL);
	}
}
