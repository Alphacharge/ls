#include "ft_ls.h"

void	print_treelvl(t_file *tree)
{
	t_file	*this = tree;

	while (this) {
		if (this->name && this->data && (!is_dotfile(this->name) || (is_dotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			ft_printf("%s", this->name);
		if (this->next && this->name && (!is_dotfile(this->name) || (is_dotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			fillup_and_gap(this->length, tree->maxlength);
		this = this->next;
		if (this == NULL){
			ft_printf("\n");
			if (tree->data && F_ISSET(*(tree->data->flags), F_RECURSIVE))
				ft_printf("\n");
		}
	}
}
