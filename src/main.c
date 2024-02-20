#include "ft_ls.h"

t_data	*init_data(unsigned short *bitmask)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		ft_error(NULL, 0);
	data->flags = bitmask;
	data->folders = NULL;
	data->tree = NULL;
	return data;
}

int main(int argc, char** argv) {
	t_data			*data;
	unsigned short	bitmask = 0;

	data = init_data(&bitmask);
	parsing(data, argc, argv);

	//sorting parameters
	data->folders = mergesortlist(data->folders);
	// bubblesort(data->folders, ft_arraycount(data->folders), F_ISSET(*(data->flags), F_REVERSE));

	//generate, sort, print and free tree for every parameter
	t_file	*current = data->folders;
	while (current != NULL) {
		DIR	*dir = opendir(current->fullpath_name);
		if (dir == NULL)
			ft_error(data, 6);
		if (!is_special_dir(current->fullpath_name) && listsize(data->folders) > 1)
			ft_printf("%s:\n", current->fullpath_name);
		loop(data, NULL, current->fullpath_name, dir);
		if (!is_special_dir(current->fullpath_name) && current->next != NULL)
			write(1, "\n", 1);
		current = current->next;
		closedir(dir);
	}
	ft_free_tree(data->folders);
	ft_free((void**)&data);
	return 0;
}