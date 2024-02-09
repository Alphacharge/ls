#include "ft_ls.h"

void	print_tree(t_file *tree, int lvl)
{
	// ft_printf("++%s\t%s\t%s\n", tree->name, tree->path, tree->fullpath_name);
	t_file	*this = tree;
	unsigned int	length;
	// if (this) {
	// 	if (this->name && this->name[0] != '.')
	// 		ft_printf("./%s:\n", this->name);
	// 	while (this && this->name && (this->name[0] != '.' || (this->name[0] == '.' && F_ISSET(*(this->data->flags), F_ALL)))) {
	// 		ft_printf("%s\t", this->name);
	// 		this = this->next;
	// 	}
	// 	ft_printf("\n\n");
	// }
	// if (this->sub)
	// 	print_tree(this->sub);

	while (this) {
		if (this->type == _DIR && this->data && F_ISSET(*(this->data->flags), F_RECURSIVE) && this->name && ft_strcmp(this->name, ".") && ft_strcmp(this->name, ".."))
			ft_printf("./%s:\n", this->fullpath_name);
		if (this->sub) {
			print_tree(this->sub, ++lvl);
		}
		if (this->name && this->data && (this->name[0] != '.' || (this->name[0] == '.' && F_ISSET(*(this->data->flags), F_ALL))))
			ft_printf("%s", this->name);
		if (this && this->name && (ft_strcmp(this->name, ".") && ft_strcmp(this->name, ".."))){
			length = this->length;
			while (length++ % 4)
				ft_printf(" ");
			ft_printf("\t");
		}
		this = this->next;
		if (this == NULL){
			ft_printf("\n");
			if (tree->data && F_ISSET(*(tree->data->flags), F_RECURSIVE))
				ft_printf("\n");
		}
	}
	//
	// if (this){
	// 	ft_printf("1\n");
	// 	if (this->name && ft_strcmp(this->name, ".") && ft_strcmp(this->name, ".."))
	// 		ft_printf("./%s:\n", this->name);
	// 	ft_printf("2\n");
	// 	while (this && this->name && this.data && (this->name[0] != '.' || (this->name[0] == '.' && F_ISSET(*(this->data->flags), F_ALL)))) {
	// 	ft_printf(".1\n");
	// 		ft_printf("%s\t\n", this->name);
	// 		this = this->next;
	// 	}
	// 	ft_printf("3\n");
	// 	this = tree;
	// 	while (this && this->name && (this->name[0] != '.' || (this->name[0] == '.' && F_ISSET(*(this->data->flags), F_ALL)))) {
	// 	ft_printf("4\n");
	// 		if (this->sub)
	// 			print_tree(this->sub);
	// 		this = this->next;
	// 	}
	// 	ft_printf("5\n");
	// 	ft_printf("\n");
	// }
}
