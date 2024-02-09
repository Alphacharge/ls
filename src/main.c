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
	//needs probably to be moved after the tree
	bubblesort(data->folders, ft_arraycount(data->folders), F_ISSET(*(data->flags), F_REVERSE));

	// ft_printf("options:\ta:%d,l:%d,t:%d,R:%d,r:%d\n", F_ISSET((*data->flags), F_ALL), F_ISSET((*data->flags), F_LONG), F_ISSET((*data->flags), F_MTIME), F_ISSET((*data->flags), F_RECURSIVE), F_ISSET((*data->flags), F_REVERSE));
	// for (int i = 0; data && data->folders && data->folders[i]; i++)
		// ft_printf("item: %s\n", data->folders[i]);

	// data->dirref = opendir(data->folders[0]);
	int	i = 0;
	while (data->folders[i] != NULL) {
		generate_tree(data, &data->tree, data->folders[i], opendir(data->folders[i]));
		i++;
	}
	// ft_printf("start printing:\n");
	data->tree = mergesortlist(data->tree);
	print_tree(data->tree, 0);
	exit (0);

	// for (int i = 1; folder != NULL; ++i, folder = argv[i]){
	// 	DIR* ref = opendir(folder);
	// 	if (ref == NULL)
	// 		return 1;
	// 	if (argc > 1)
	// 		ft_printf("%s:\n", folder);
	// 	// ft_printf("fd:%d,flags:%d,len:%d,loc:%d,seek:%d,size:%d\n", ref->__dd_fd, ref->__dd_flags, ref->__dd_len, ref->__dd_loc, ref->__dd_seek, ref->__dd_size);
	// 	// ft_printf("buf:%s\n\n", ref->__dd_buf);
	// 	for (struct dirent* dir = readdir(ref); dir != NULL; dir = readdir(ref)) {
	// 		//Mac
	// 		if (SYSTEM && dir && OFFSET < 3)
	// 			continue;
	// 		//Linux
	// 		else if (!SYSTEM && dir && OFFSET < 3)
	// 			continue;
	// 		ft_printf("%d,\t%s\t%d\n", dir->d_ino, dir->d_name, OFFSET);
	// 	}
	// }

	return 0;
}