#include "ft_ls.h"

void	print_treelvl(t_file **tree)
{
	t_file	*this = *tree;

	while (this) {
		//print names
		if (this->name && this->data)
			ft_printf("%s", this->name);
		//gaps 4 stdout
		if (this->next && this->next->name && F_ISSET(*(this->data->flags), F_STDOUT))
			fillup_and_gap(this->length, (*tree)->maxlength);
		else if (this->next && this->next->name && !F_ISSET(*(this->data->flags), F_STDOUT))
			(DEBUG) ? (write(1, "6\n", 2)) : (write(1, "\n", 1));
		this = this->next;
		if (this == NULL)
			(DEBUG) ? (write(1, "7\n", 2)) : (write(1, "\n", 1));
	}
}
