#include "ft_ls.h"

bool	isDotfile(char *filename)
{
	if (!filename)
		return false;
	if (filename[0] == '.')
		return true;
	return false;
}
