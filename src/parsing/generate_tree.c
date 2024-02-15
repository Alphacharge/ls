#include "ft_ls.h"
#include <sys/errno.h>

void	generate_tree(t_data *data, char *path, DIR *ref)
{
	if (ref == NULL)
		ft_error(data, 6);
	while (ref != NULL) {
		if (data->treeused == data->treesize)
			realloc_array(data);
		
		struct dirent *dir = readdir(ref);
		if (dir != NULL) {
			data->treeused++;
			set_file_type(&data->tree[data->treeused], dir->d_type);
			data->tree[data->treeused].name = ft_strdup(dir->d_name);
			data->tree[data->treeused].path = path;
			data->tree[data->treeused].fullpath_name = ft_multijoin(false, 3, path, "/", dir->d_name);
			ft_printf("PATH:%s\n", data->tree[data->treeused].fullpath_name);
			data->tree[data->treeused].length = dir->d_namlen;

			if (data->tree[data->treeused].name == NULL || data->tree[data->treeused].fullpath_name == NULL)
				ft_error(data, 5);
			if (F_ISSET(*data->flags, F_LONG) && lstat(data->tree[data->treeused].fullpath_name, &data->tree[data->treeused].stat) < 0)
				ft_error(data, 4);
			if (!is_special_dir(data->tree[data->treeused].name) && F_ISSET(*(data->flags), F_RECURSIVE) && data->tree[data->treeused].type == _DIR)
			{
				DIR	*dir = opendir(data->tree[data->treeused].fullpath_name);
				if (dir == NULL) {
					perror(data->tree[data->treeused].fullpath_name);
					break;
				}
				generate_tree(data, data->tree[data->treeused].fullpath_name, dir);
			}
		} else {
			break;
		}
	}
	closedir(ref);
}
