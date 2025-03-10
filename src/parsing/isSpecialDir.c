#include "ft_ls.h"

/**
 * Checks if a given filename represents a special directory ('.' or '..').
 * @param fileName - Pointer to the string containing the filename.
 * @return - Returns true if the filename is '.' or '..', false otherwise.
 */
bool	isSpecialDir(char *fileName)
{
	if (fileName && (!ft_strcmp(fileName, ".") || !ft_strcmp(fileName, "..")))
		return true;
	return false;
}
