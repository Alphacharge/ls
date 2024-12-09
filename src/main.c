#include "ft_ls.h"

/**
 * @brief Initializes a new t_data structure.
 *
 * This function allocates memory for a t_data structure and initializes its fields.
 * If memory allocation fails, it prints an error message to STDERR and exits the program.
 *
 * @param bitmask Pointer to an unsigned short bitmask representing flags for the data structure.
 * @return A pointer to the newly initialized t_data structure.
 */
t_data	*init_data(unsigned short *bitmask)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL) {
		ft_putstr_fd("data malloc error\n", STDERR_FILENO);
		ft_error(NULL, 0);
	}
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
	data->folders = mergesortFileList(data->folders);

	//generate, sort, print and free tree for every parameter
	t_file	*current = data->folders;
	while (current != NULL) {
		DIR	*dir = opendir(current->fullPathName);
		if (dir == NULL){
			perror(current->fullPathName);
			current = current->next;
			continue;
		}
		if (!isSpecialDir(current->fullPathName))
			ft_printf("%s:\n", current->fullPathName);
		loop(&data, NULL, current->fullPathName, dir);
		if (!isSpecialDir(current->fullPathName) && current->next != NULL)
			write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
	ft_free_tree(data->folders);
	ft_free((void**)&data);
	return 0;
}


//listxattr --> fixed by >0 ???
//sticky bit
//error if option appears after arg
//error if option not exists