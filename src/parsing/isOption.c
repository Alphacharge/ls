#include "ft_ls.h"

bool	isOption(char *argv)
{
	if (argv && argv[0] == '-')
		return true;
	return false;
}
