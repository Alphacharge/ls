#include "ft_ls.h"

void	get_options(t_data *data, char* argv)
{
	while (data && argv && *argv) {
		if (*argv == 'l')
			data->longformat = true;
		else if (*argv == 'a')
			data->all = true;
		else if (*argv == 'u')
			data->mtime = true;
		else if (*argv == 'R')
			data->recursive = true;
		else if (*argv == 'r')
			data->reversed = true;
		argv++;
	}
}
