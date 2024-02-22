#include "ft_ls.h"

bool	isSpecialDir(char *filename)
{
	if (!filename)
		return false;
	if (!ft_strcmp(filename, ".") || !ft_strcmp(filename, ".."))
		return true;
	return false;
}
