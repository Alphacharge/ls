#include "ft_ls.h"

/**
 * Recursive function to handle directory traversal and printing in the ft_ls program.
 * Prints information about files and directories specified by path, either directly or recursively
 * depending on flags set in data. Handles memory allocation for new t_file structures and associated
 * strings. Prints formatted output based on flags, and recursively calls itself for subdirectories
 * if F_RECURSIVE flag is set.
 * @param data - Double pointer to t_data structure containing program state and flags.
 * @param treelvl - Double pointer to t_file structure representing current level directory contents.
 * @param path - String representing the current directory path being processed.
 * @param ref - Pointer to DIR structure representing the directory stream to be read.
 */
void	loop(t_data **data, t_file **treelvl, char *path, DIR *ref)
{
	static unsigned int	maxFileNameLength = 0;
	static unsigned int	maxLinks = 0;
	static unsigned int	maxBytes = 0;
	static unsigned int	maxUserLength = 0;
	static unsigned int	maxGroupLength = 0;
	static unsigned int	totalBlocks = 0;

	// Print file information and generate child trees if recursive
	if (treelvl != NULL)
	{
		*treelvl = mergesortFileList(*treelvl);
		if (F_ISSET((*(*data)->flags), F_LONG))
			printLongTreelvl(treelvl);
		else
			printTreelvl(treelvl);

		// If recursive, generate child trees for directories
		if (F_ISSET((*(*data)->flags), F_RECURSIVE))
		{
			maxFileNameLength = maxLinks = maxBytes = maxUserLength = maxGroupLength = totalBlocks = 0;
			t_file *current = *treelvl;
			while (current)
			{
				if (current->fileType == _DIR
					&& !isSpecialDir(current->fileName)
					&& (!isDotfile(current->fileName) || (isDotfile(current->fileName) && F_ISSET(*(*data)->flags, F_ALL))))
				{
					DIR	*dir = opendir(current->fullPathName);
					ft_printf("\n%s:\n", current->fullPathName);
					if (dir == NULL) {
						ft_putstr_fd(current->fullPathName, 2);
						perror(current->fullPathName);
						current = current->next;
						continue;
					}
					loop(data, NULL, current->fullPathName, dir);
				}
				current = current->next;
			}
		}
		ft_free_tree(*treelvl);
	}
	// If no files to print, generate file list from directory stream ref
	else
	{
		if (ref == NULL)
			return ;
		struct dirent *dir = readdir(ref);
		t_file	*head = NULL;
		t_file	*last = NULL;
		while (dir != NULL) {
			if (isDotfile(dir->d_name) && !F_ISSET((*(*data)->flags), F_ALL)){
				dir = readdir(ref);
				continue;
			}
			t_file	*new = listNew(*data);
			if (new == NULL)
				ft_error(*data, 1);
			setFileType(new, dir->d_type);
			new->fileName = ft_strdup(dir->d_name);
			new->lowercaseName = ft_strlower(ft_strdup(dir->d_name));
			if (new->fileName == NULL || new->lowercaseName == NULL){
				ft_putstr_fd("file name malloc error\n", STDERR_FILENO);
				ft_free_tree(new);
				ft_error(*data, 1);
			}
			char *separator = (!path || path[0] == '\0' || path[ft_strlen(path) - 1] == '/') ? "" : "/";
			new->fullPathName = ft_multijoin(false, 3, path, separator, dir->d_name);
			if (new->fullPathName == NULL){
				ft_putstr_fd("path malloc error\n", STDERR_FILENO);
				ft_free_tree(new);
				ft_error(*data, 1);
			}
			new->fileNameLength = NAMELENGTH;
			if (new->fileNameLength > maxFileNameLength){
				maxFileNameLength = new->fileNameLength;
				new->maxFileNameLength = new->fileNameLength;
			}
			else
				new->maxFileNameLength = maxFileNameLength;
			if ((F_ISSET(*new->data->flags, F_LONG) || F_ISSET(*new->data->flags, F_MTIME))
				&& lstat(new->fullPathName, &new->stat) < 0){
				perror("lstat");
				ft_free_tree(new);
				ft_error(*data, 1);
			}
			if (F_ISSET(*new->data->flags, F_LONG)) {
				struct passwd	*pwd;
				struct group	*grp;
				pwd = getpwuid(new->stat.st_uid);
				if (pwd == NULL){
					ft_free_tree(new);
					ft_error(*data, 1);
				}
				grp = getgrgid(new->stat.st_gid);
				if (grp == NULL){
					ft_free_tree(new);
					ft_error(*data, 1);
				}
				new->userLength = ft_strlen(pwd->pw_name);
				if (new->userLength > maxUserLength) {
					maxUserLength = new->userLength;
					new->maxUserLength = new->userLength;
				}
				else
					new->maxUserLength = maxUserLength;
				new->userName = ft_strdup(pwd->pw_name);
				if (new->userName == NULL){
					ft_putstr_fd("user malloc error\n", STDERR_FILENO);
					ft_free_tree(new);
					ft_error(*data, 1);
				}
				new->groupLength = ft_strlen(grp->gr_name);
				if (new->groupLength > maxGroupLength) {
					maxGroupLength = new->groupLength;
					new->maxGroupLength = new->groupLength;
				}
				else
					new->maxGroupLength = maxGroupLength;
				new->groupName = ft_strdup(grp->gr_name);
				if (new->groupName == NULL){
					ft_putstr_fd("group malloc error\n", 2);
					ft_free_tree(new);
					ft_error(*data, 1);
				}
				if (DEBUGLVL > 0)
					ft_printf("%snstatlinks:%d,\tcurrentmaxlinks:%d\n%s", RED, new->stat.st_nlink, maxLinks, WHITE);
				if (new->stat.st_nlink > maxLinks) {
					maxLinks = new->stat.st_nlink;
					new->maxLinks = new->stat.st_nlink;
				}
				else
					new->maxLinks = maxLinks;
				if (new->stat.st_size > maxBytes) {
					maxBytes = new->stat.st_size;
					new->maxBytes = new->stat.st_size;
				}
				else
					new->maxBytes = maxBytes;
				totalBlocks += new->stat.st_blocks / BLOCK_SIZE;
				new->totalBlocks = totalBlocks;
			}
			if (head == NULL) {
				head = new;
			} else {
				last->next = new;
			}
			last = new;
			dir = readdir(ref);
		}
		// Update max Values for cols
		t_file	*update = head;
		while (update && update->next){
			update->maxFileNameLength = maxFileNameLength;
			if (F_ISSET(*head->data->flags, F_LONG)) {
				update->maxLinks = maxLinks;
				update->maxBytes = maxBytes;
				update->maxUserLength = maxUserLength;
				update->maxGroupLength = maxGroupLength;
				update->totalBlocks = totalBlocks;
			}
			update = update->next;
		}
		if (ref)
			closedir(ref);
		if (head != NULL)
			loop(data, &head, head->fullPathName, NULL);
	}
}
