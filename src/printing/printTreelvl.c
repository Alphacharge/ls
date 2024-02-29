#include "ft_ls.h"

void	printTreelvl(t_file **tree)
{
	t_file	*this = *tree;

	while (this) {
		//print names
		if (this->fileName && this->data)
			ft_putstr_fd(this->fileName, 1);
		//gaps 4 stdout
		if (this->next && this->next->fileName) {
			if (F_ISSET(*(this->data->flags), F_STDOUT))
				insertPadding(this->fileNameLength, (*tree)->maxFileNameLength);
			else
				write(1, "\n", 1);
		}
		this = this->next;
		if (this == NULL)
			write(1, "\n", 1);
	}
}
