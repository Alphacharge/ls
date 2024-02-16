#include "ft_ls.h"

void	get_options(t_data *data, char* argv)
{
	while (data && argv && *argv) {
		if (*argv == 'l')
			F_SET(*(data->flags), F_LONG);
		else if (*argv == 'a')
			F_SET(*(data->flags), F_ALL);
		else if (*argv == 't')
			F_SET(*(data->flags), F_MTIME);
		else if (*argv == 'R')
			F_SET(*(data->flags), F_RECURSIVE);
		else if (*argv == 'r')
			F_SET(*(data->flags), F_REVERSE);
		argv++;
	}
}
