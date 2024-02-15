#include "ft_ls.h"
#include <sys/errno.h>

void	generate_tree(t_data *data, t_file **treelvl, char *path, DIR *ref)
{
	if (ref == NULL)
		ft_error(data, 6);
	while (ref != NULL) {
		t_file	*new = new_node(data);
		if (new == NULL)
			ft_error(data, 3);
		if (*treelvl == NULL)
			*treelvl = new;
		else
		{
			t_file	*last = *treelvl;
			while (last && last->next)
				last = last->next;
			last->next = new;
		}

		struct dirent *dir = readdir(ref);
		if (dir != NULL) {
			set_file_type(new, dir->d_type);
			new->name = ft_strdup(dir->d_name);
			new->path = path;
			new->fullpath_name = ft_multijoin(false, 3, path, "/", dir->d_name);
			new->length = dir->d_namlen;

			if (new->name == NULL || new->fullpath_name == NULL)
				ft_error(data, 5);
			if (F_ISSET(*new->data->flags, F_LONG) && lstat(new->fullpath_name, &new->stat) < 0)
				ft_error(data, 4);
			if (!is_special_dir(new->name) && F_ISSET(*(data->flags), F_RECURSIVE) && new->type == _DIR)
			{
				DIR	*dir = opendir(new->fullpath_name);
				if (dir == NULL) {
					perror(new->fullpath_name);
					break;
				}
				generate_tree(data, &new->sub, new->fullpath_name, dir);
			}
		} else {
			break;
		}
	}
	closedir(ref);
	(*treelvl)->listsize = listsize(*treelvl);
}
