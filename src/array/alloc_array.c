#include "ft_ls.h"

void	alloc_array(t_data *data)
{
	if (F_ISSET(*(data->flags), F_RECURSIVE))
	{
		data->treesize = 1000;
		data->tree = malloc(data->treesize * sizeof(t_file));
	}
	else
	{
		data->treesize = 100;
		data->tree = malloc(data->treesize * sizeof(t_file));
	}
	if (data->tree == NULL)
			ft_error(data, 3);
}
