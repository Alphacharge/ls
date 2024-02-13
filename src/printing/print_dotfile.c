#include "ft_ls.h"

bool	print_dotfile(unsigned short *flags, char *filename)
{
	if (is_dotfile(filename) && F_ISSET(*flags, F_ALL))
		return true;
	return false;
}
