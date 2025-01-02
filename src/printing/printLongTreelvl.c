#include "ft_ls.h"

/**
 * Prints detailed information about files in a tree-like format, including permissions, owners, sizes, and timestamps.
 * @param tree - Double pointer to the t_file structure representing the tree of files/directories.
 */
void	printLongTreelvl(t_file **tree)
{
	t_file	*this = *tree;
	char	permissions[11];
	char	*month;
	
	ft_printf("total %d\n", this->totalBlocks);
	while (this) {
		ft_memset(permissions, '-', sizeof(permissions));
		permissions[10] = ' ';

		// Set file type indicator
		if (this->fileType == _DIR)
			permissions[0] = 'd';
		else if (this->fileType == _LINK)
			permissions[0] = 'l';

		// Set permissions for user
		if (this->stat.st_mode & S_IRUSR)
			permissions[1] = 'r';
		if (this->stat.st_mode & S_IWUSR)
			permissions[2] = 'w';
		if (this->stat.st_mode & S_IXUSR)
			permissions[3] = 'x';

		// Set permissions for group
		if (this->stat.st_mode & S_IRGRP)
			permissions[4] = 'r';
		if (this->stat.st_mode & S_IWGRP)
			permissions[5] = 'w';
		if (this->stat.st_mode & S_IXGRP)
			permissions[6] = 'x';

		// Set permissions for others
		if (this->stat.st_mode & S_IROTH)
			permissions[7] = 'r';
		if (this->stat.st_mode & S_IWOTH)
			permissions[8] = 'w';
		if (this->stat.st_mode & S_IXOTH)
			permissions[9] = 'x';

		// Set sticky bit
		if (this->stat.st_mode & S_ISVTX)
			permissions[9] = 'T';
		// Check for extended attributes
		char	buffer[MAX_XATTR_SIZE];
		if (LISTXATTR > 0)
			permissions[10] = '@';

		// Print: permissions, linkcount, userpem, grouppem, filesize
		write(STDOUT_FILENO, permissions, 11);
		printValue(&this, this->maxLinks, 1);
		printUserGroup(this->userLength, this->maxUserLength, this->userName);
		printUserGroup(this->groupLength, this->maxGroupLength, this->groupName);
		write(STDOUT_FILENO, " ", 1);
		printValue(&this, this->maxBytes, 0);

		// Print month and day from timestamp
		month = ctime(&this->TIME_SEC);
		if (!month)
			ft_error(this->data, 1);
		month = &month[3]; // Skip day of the week
		//print year instead of time if older than 6 months
		if (this->TIME_SEC < this->data->sixmonthsago) {
			ft_memmove(&month[8], &month[16], 5);
			month[13] = '\0';
		}
		write(STDOUT_FILENO, month, 13);
		write(STDOUT_FILENO, " ", 1);

		printFilename(&this);
		write(STDOUT_FILENO, "\n", 1);
		this = this->next;
	}
}
