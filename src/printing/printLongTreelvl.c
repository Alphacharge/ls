#include "ft_ls.h"

void	printLongTreelvl(t_file **tree)
{
	t_file	*this = *tree;
	char	permissions[11];
	
	ft_memset(permissions, '-', sizeof(permissions));
	permissions[10] = ' ';

	while (this) {
		//filetype
		if (this->fileType == _DIR)
			permissions[0] = 'd';
		else if (this->fileType == _LINK)
			permissions[0] = 'l';
		//permissions user
		if (this->stat.st_mode & S_IRUSR)
			permissions[1] = 'r';
		if (this->stat.st_mode & S_IWUSR)
			permissions[2] = 'w';
		if (this->stat.st_mode & S_IXUSR)
			permissions[3] = 'x';
		//permissions group
		if (this->stat.st_mode & S_IRGRP)
			permissions[4] = 'r';
		if (this->stat.st_mode & S_IWGRP)
			permissions[5] = 'w';
		if (this->stat.st_mode & S_IXGRP)
			permissions[6] = 'x';
		//permissions other
		if (this->stat.st_mode & S_IROTH)
			permissions[7] = 'r';
		if (this->stat.st_mode & S_IWOTH)
			permissions[8] = 'w';
		if (this->stat.st_mode & S_IXOTH)
			permissions[9] = 'x';
		//extendend attr
		if (listxattr(this->fullPathName, NULL, 0, 0) != 0)
			permissions[10] = '@';
		// this->stat.st_nlink
		write(1, permissions, 11);
		if (this->fileName && this->data)
			ft_printf("%s", this->fileName);
		//gaps 4 stdout
		if (this->next && this->next->fileName && F_ISSET(*(this->data->flags), F_STDOUT))
			insertPadding(this->fileNameLength, (*tree)->maxFileNameLength);
		else if (this->next && this->next->fileName && !F_ISSET(*(this->data->flags), F_STDOUT))
			(DEBUG) ? (write(1, "6\n", 2)) : (write(1, "\n", 1));
		this = this->next;
		if (this == NULL)
			(DEBUG) ? (write(1, "7\n", 2)) : (write(1, "\n", 1));
	}
}
