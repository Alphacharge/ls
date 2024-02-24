#include "ft_ls.h"

t_data	*init_data(unsigned short *bitmask)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		ft_error(NULL, 0);
	data->flags = bitmask;
	data->folders = NULL;
	return data;
}

int main(int argc, char** argv) {
	t_data			*data;
	unsigned short	bitmask = 0;

	data = init_data(&bitmask);
	detectOutputMode(data);
	parsing(data, argc, argv);

	//sorting parameters
	F_SET(bitmask, F_FOLDERSORT);
	data->folders = mergesortFileList(data->folders);
	F_CLEAR(bitmask, F_FOLDERSORT);

	//generate, sort, print and free tree for every parameter
	t_file	*current = data->folders;
	while (current != NULL) {
		DIR	*dir = opendir(current->fullPathName);
		if (dir == NULL){
			perror(current->fullPathName);
			ft_error(data, 6);
		}
		if (!isSpecialDir(current->fullPathName))
			(DEBUG) ? (ft_printf("%s:0\n", current->fullPathName)) : ft_printf("%s:\n", current->fullPathName);
		loop(&data, NULL, current->fullPathName, dir);
		if (!isSpecialDir(current->fullPathName) && current->next != NULL)
			(DEBUG) ? (write(1, "9\n", 2)) : (write(1, "\n", 1));
		current = current->next;
	}
	ft_free_tree(data->folders);
	ft_free((void**)&data);
	return 0;
}