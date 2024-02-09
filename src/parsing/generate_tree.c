#include "ft_ls.h"
#include <sys/errno.h>

void	generate_tree(t_data *data, t_file **treelvl, char *path, DIR *ref)
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
			char	*file = ft_strjoin(path, dir->d_name);
			if (file == NULL)
				ft_error(data, 5);
			if (lstat(file, &new->stat) < 0){
				ft_free(file);
				ft_error(data, 4);
			}
			if (!SYSTEM && OFFSET > 2 && new->type == _DIR)
				generate_tree(data, &new->sub, file, opendir(file));
			ft_free(file);
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
