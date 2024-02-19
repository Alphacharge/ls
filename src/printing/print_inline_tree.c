#include "ft_ls.h"

void	print_inline_tree(t_file *tree)
{
	t_file	*this = tree;

	while (this) {
		if (this->name)
			ft_printf("%s", this->name);
		if (this->next && this->name)
			fillup_and_gap(this->length, tree->maxlength);
		ft_printf("\t");
		this = this->next;
		if (this == NULL)
			ft_printf("\n");
	}
}
