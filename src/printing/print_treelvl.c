#include "ft_ls.h"

void	print_treelvl(t_file *tree)
{
	t_file	*this = tree;

	while (this) {
		if (this->name && this->data && (!isDotfile(this->name) || (isDotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			ft_printf("%s", this->name);
		if (this->next && this->next->name && \
			(!isDotfile(this->name) || (isDotfile(this->next->name) && F_ISSET(*(this->data->flags), F_ALL))) && \
			(!isDotfile(this->next->name) || (isDotfile(this->next->name) && F_ISSET(*(this->data->flags), F_ALL))))
			fillup_and_gap(this->data->flags, this->length, tree->maxlength);
		this = this->next;
		// ft_printf("this:%p:%s\n", this, this->fullpath_name);
		if (this == NULL){
			write(1, "\n", 1);
			if (tree->data && F_ISSET(*(tree->data->flags), F_RECURSIVE))
				ft_printf("\n");
		}
	}
		// if (!F_ISSET(*(tree->data->flags), F_STDOUT))
			// write(1, "\n", 1);
	// if (!F_ISSET(*(tree->data->flags), F_STDOUT))
	// 	write(1, "8\n", 2);
}
