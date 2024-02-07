#include "ft_ls.h"

void	generate_tree(t_data *data, t_file **treelvl, DIR *ref)
{
	while (ref != NULL) {
		t_file	*new = ft_calloc(1, sizeof(t_file));
		if (new == NULL)
			ft_error(data, 3);
		new->next = NULL;
		new->data = data;
		if (*treelvl == NULL)
			*treelvl = new;
		else {
			t_file	*last = *treelvl;
			while (last && last->next)
				last = last->next;
			last->next = new;
		}
		struct dirent *dir = readdir(ref);
		if (dir != NULL) {
			set_file_type(new, dir->d_type);
			if (lstat(dir->d_name, &new->stat) < 0)
				ft_error(data, 4);
			ft_printf("->%s\n", dir->d_name);
			if (!SYSTEM && OFFSET > 2 && new->type == _DIR) {
				// char *path = ft_strjoin("./", dir->d_name);
				// generate_tree(data, &new->sub, opendir(path));
				// free(path);
				generate_tree(data, &new->sub, opendir(dir->d_name));

				//continue here and figure out why it doesn't work for sub dirs
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
