#include "ft_ls.h"

void	print_treelvl(t_file *tree)
{
	t_file	*this = tree;

	while (this) {
		if (this->name && this->data && (!isDotfile(this->name) || (isDotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			ft_printf("%s", this->name);
		if (this->next && this->name && (!isDotfile(this->name) || (isDotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			fillup_and_gap(this->data->flags, this->length, tree->maxlength);
		this = this->next;
		if (this == NULL){
			ft_printf("\n");
			if (tree->data && F_ISSET(*(tree->data->flags), F_RECURSIVE))
				ft_printf("\n");
		}
	}
}
