#include "ft_ls.h"

//-t-r doesn't change the printing
void	print_tree(t_file *tree, int lvl)
{
	t_file	*this = tree;

	while (this) {
		if (lvl == 0 && this->data && F_ISSET(*(this->data->flags), F_RECURSIVE))
		{
			ft_printf("%s", this->name);
			this = this->next;
			if (this)
				fillup_and_gap(this->length, tree->maxlength);
			else
				print_tree(tree, ++lvl);
			continue;
		}
		if (this->type == _DIR && this->data && F_ISSET(*(this->data->flags), F_RECURSIVE) && this->name && (!is_dotfile(this->name) || print_dotfile(this->data->flags, this->name)))
			ft_printf("./%s:\n", this->fullpath_name);
		if (this->name && this->data && (!is_dotfile(this->name) || (is_dotfile(this->name) && F_ISSET(*(this->data->flags), F_ALL))))
			ft_printf("%s", this->name);
		if (this && this->next && this->name && !is_special_dir(this->name))
			fillup_and_gap(this->length, tree->maxlength);
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
