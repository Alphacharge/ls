#include "ft_ls.h"

/**
 * Prints filenames in a tree structure, optionally inserting padding spaces or newlines between entries.
 * @param tree - Double pointer to the t_file structure representing the tree of files/directories.
 */
void	printTreelvl(t_file **tree)
{
	t_file	*this = *tree;

	while (this) {
		//print names
		if (this->fileName)
			ft_putstr_fd(this->fileName, STDOUT_FILENO);
		if (this->next && this->next->fileName && this->data) {
			//padding just 4 stdout
			if (F_ISSET(*(this->data->flags), F_STDOUT))
				insertPadding(this->fileNameLength, (*tree)->maxFileNameLength);
			else
				write(STDOUT_FILENO, "\n", 1);
		}
		this = this->next;
		if (this == NULL)
			write(STDOUT_FILENO, "\n", 1);
	}
}
