#include "ft_ls.h"

/**
 * Checks if a given filename represents a dotfile (hidden file starting with '.').
 * @param fileName - Pointer to the string containing the filename.
 * @return - Returns true if the filename is a dotfile, false otherwise.
 */
bool	isDotfile(char *fileName)
{
	if (fileName && fileName[0] == '.')
		return true;
	return false;
}
