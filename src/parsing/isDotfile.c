#include "ft_ls.h"

bool	isDotfile(char *fileName)
{
	if (!fileName)
		return false;
	if (fileName[0] == '.')
		return true;
	return false;
}
