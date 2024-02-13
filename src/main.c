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
	bubblesort(data->folders, ft_arraycount(data->folders), F_ISSET(*(data->flags), F_REVERSE));

	//generate, sort, print and free tree for every parameter
	int	i = 0;
	while (data->folders[i] != NULL) {
		DIR	*dir = opendir(data->folders[i]);
		if (dir == NULL)
			ft_error(data, 6);
		generate_tree(data, &data->tree, data->folders[i], dir);
		data->tree = mergesortlist(data->tree);
		print_tree(data->tree, 1);
	exit (0);
		ft_free_tree(data->tree);
		i++;
	}

	return 0;
}