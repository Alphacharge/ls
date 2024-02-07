#include "ft_ls.h"

bool	is_option(char *argv)
{
	if (argv && argv[0] == '-')
		return true;
	return false;
}
