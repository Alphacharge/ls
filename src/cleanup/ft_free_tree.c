#include "ft_ls.h"

void	ft_free_tree(t_data *data)
{
	size_t	i = 0;

	while (i < data->treeused) {
		ft_free(data->tree[i].fullpath_name);
		ft_free(data->tree[i].name);
		i++;
	}
	ft_free(data->tree);
}
