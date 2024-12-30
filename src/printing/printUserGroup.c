#include "ft_ls.h"

/**
 * Prints a user or group name with padding spaces to align it in a tabular format.
 * @param length - Length of the current user or group name.
 * @param maxLength - Maximum length of user or group names in the current context.
 * @param value - Pointer to the string containing the user or group name to be printed.
 */
void	printUserGroup(unsigned int length, unsigned int maxLength, char *value)
{
	write(STDOUT_FILENO, " ", 1);
	while (length++ < maxLength)
		write(STDOUT_FILENO, " ", 1);
	ft_putstr_fd(value, STDOUT_FILENO);
	// write(STDOUT_FILENO, " ", 1);
}
