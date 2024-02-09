#include "ft_ls.h"
#include <sys/errno.h>

void	generate_tree(t_data *data, t_file **treelvl, char *path, DIR *ref)
{
	while (ref != NULL) {
		t_file	*new = ft_calloc(1, sizeof(t_file));
		if (new == NULL)
			ft_error(data, 3);
		new->next = NULL;
		new->name = NULL;
		new->fullpath_name = NULL;
		new->data = data;
		new->length = 0;
		if (*treelvl == NULL){
			*treelvl = new;
			// ft_printf("/%s\n", new->name);
		}
		else {
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
			// ft_printf("--%s\t%s\t%s\n", new->name, new->path, new->fullpath_name);
			if (new->name == NULL || new->fullpath_name == NULL)
				ft_error(data, 5);
			if (lstat(new->fullpath_name, &new->stat) < 0)
				ft_error(data, 4);
			// ft_printf("///%s\n", new->name);
			if (SYSTEM && OFFSET > 2 && F_ISSET(*(data->flags), F_RECURSIVE) && new->type == _DIR) {
			// ft_printf("//////%s\n", new->fullpath_name);
				generate_tree(data, &new->sub, new->fullpath_name, opendir(new->fullpath_name));
			}
		} else {
			break;
		}
	}
	// 	for (int i = 0; data->folders[i]; i++) {
	// 	new->next = NULL;
	// 	DIR	*dir = opendir(data->folders[i]);
	// 	if (dir == NULL)
	// 	if (dir.)
		
	// }
}
