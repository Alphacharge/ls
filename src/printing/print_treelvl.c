#include "ft_ls.h"

void	print_treelvl(t_file *tree)
{
	t_file	*this = tree;

	while (this) {
		//print names
		if (this->name && this->data && \
			(!isDotfile(this->name) || \
			F_ISSET(*(this->data->flags), F_ALL)))
			ft_printf("%s", this->name);
		//gaps 4 stdout
		if (this->next && this->next->name && F_ISSET(*(this->data->flags), F_STDOUT))
			fillup_and_gap(this->length, tree->maxlength);
		else if (this->next && this->next->name && !F_ISSET(*(this->data->flags), F_STDOUT))
			(DEBUG) ? (write(1, "6\n", 2)) : (write(1, "\n", 1));
		this = this->next;
		// ft_printf("this:%p:%s\n", this, this->fullpath_name);
		if (this == NULL){
			(DEBUG) ? (write(1, "7\n", 2)) : (write(1, "\n", 1));
			// if (tree->data && F_ISSET(*(tree->data->flags), F_RECURSIVE))
			// 	(DEBUG) ? (ft_printf("8\n")) : (ft_printf("\n"));
		}
	}
		// if (!F_ISSET(*(tree->data->flags), F_STDOUT))
			// write(1, "\n", 1);
	// if (!F_ISSET(*(tree->data->flags), F_STDOUT))
	// 	write(1, "8\n", 2);
}
