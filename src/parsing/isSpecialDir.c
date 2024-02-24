#include "ft_ls.h"

bool	isSpecialDir(char *fileName)
{
	if (!fileName)
		return false;
	if (!ft_strcmp(fileName, ".") || !ft_strcmp(fileName, ".."))
		return true;
	return false;
}
