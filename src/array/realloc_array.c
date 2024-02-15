#include "ft_ls.h"

void	realloc_array(t_data *data)
{
	t_file	*new;
	size_t	i = 0;

	if (F_ISSET(*(data->flags), F_RECURSIVE))
	{
		if (SIZE_MAX / 3 - 1 < data->treesize)
			ft_error(data, 3);
		data->treesize *= 3;
		new = malloc(data->treesize * sizeof(t_file));
	}
	else
	{
		if (SIZE_MAX / 2 - 1 < data->treesize)
			ft_error(data, 3);
		data->treesize *= 2;
		new = malloc(data->treesize * sizeof(t_file));
	}
	if (new == NULL)
		ft_error(data, 3);
	while (i < data->treeused)
	{
		new[i] = data->tree[i];
		i++;
	}
	ft_free_tree(data);
	data->tree = new;
}
