#include "ft_ls.h"

void	print_tree(t_file *tree, int lvl)
{
	t_file	*this = tree;
	unsigned int	length;

	while (this) {
		if (this->type == _DIR && this->data && F_ISSET(*(this->data->flags), F_RECURSIVE) && this->name && (!is_dotfile(this->name) || print_dotfile(this->data->flags, this->name)))
			ft_printf("./%s:\n", this->fullpath_name);
		if (this->name && this->data && (!is_dotfile(this->name) || (is_dotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			ft_printf("%s", this->name);
		if (this && this->name && !is_special_dir(this->name))
		{
			length = this->length;
			while (length++ % 4)
				ft_printf(" ");
			ft_printf("\t");
		}
		if (this->sub && this->name && this->data && (!is_dotfile(this->name) || print_dotfile(this->data->flags, this->name))) {
			print_tree(this->sub, ++lvl);
		}
		this = this->next;
		if (this == NULL){
			ft_printf("\n");
			if (tree->data && F_ISSET(*(tree->data->flags), F_RECURSIVE))
				ft_printf("\n");
		}
	}
}
