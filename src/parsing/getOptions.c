#include "ft_ls.h"

/**
 * Parses command-line options represented as characters and sets corresponding flags in the data structure.
 * @param data - Pointer to the data structure holding program flags.
 * @param argv - String of characters representing command-line options.
 */
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
			case '-':
				break;
			default:
				ft_putstr_fd("ft_ls: illegal option -- ", 2);
				ft_putchar_fd(*argv, 2);
				ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
				ft_error(data, 1);
		}
		argv++;
	}
}
