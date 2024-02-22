#include "ft_ls.h"

void	getOptions(t_data *data, char* argv)
{
	while (data && argv && *argv)
	{
		switch (*argv)
		{
			case 'l':
				F_SET(*(data->flags), F_LONG);
				break;
			case 'a':
				F_SET(*(data->flags), F_ALL);
				break;
			case 't':
				F_SET(*(data->flags), F_MTIME);
				break;
			case 'R':
				F_SET(*(data->flags), F_RECURSIVE);
				break;
			case 'r':
				F_SET(*(data->flags), F_REVERSE);
				break;
		}
		argv++;
	}
}
