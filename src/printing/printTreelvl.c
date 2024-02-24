#include "ft_ls.h"

void	printTreelvl(t_file **tree)
{
	t_file	*this = *tree;

	while (this) {
		//print names
		if (this->fileName && this->data)
			ft_putstr_fd(this->fileName, 1);
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
