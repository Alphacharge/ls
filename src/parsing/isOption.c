#include "ft_ls.h"

/**
 * Checks if a given string represents a command-line option, indicated by starting with '-'.
 * @param argv - Pointer to the string to check.
 * @return - Returns true if the string is a command-line option, false otherwise.
 */
bool	isOption(char *argv)
{
	if (argv && argv[0] == '-')
		return true;
	return false;
}
