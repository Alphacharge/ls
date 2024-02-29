#include "ft_ls.h"

void	ft_error(t_data *data, unsigned int code)
{
	if (code == 0)
		ft_free((void**)&(data));
	else if (code == 1) {
		ft_free_tree(data->folders);
		ft_free((void**)&(data));
	}
	exit (EXIT_FAILURE);
}
