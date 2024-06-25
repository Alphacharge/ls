#include "ft_ls.h"

/**
 * Inserts padding spaces and tabs to align filenames in a tabular format based on given lengths.
 * @param fileNameLength - Length of the current filename.
 * @param maxFileNameLength - Maximum length of filenames in the current context.
 */
void	insertPadding(unsigned int fileNameLength, unsigned int maxFileNameLength)
{
	unsigned int spaces_needed = (TAB_WIDTH - (fileNameLength % TAB_WIDTH)) % TAB_WIDTH;
	for (unsigned int i = 0; i < spaces_needed; ++i) {
		write(STDOUT_FILENO, " ", 1);
		fileNameLength++;
	}

	while (fileNameLength < maxFileNameLength) {
		write(STDOUT_FILENO, "\t", 1);
		fileNameLength += TAB_WIDTH;
	}
	write(STDOUT_FILENO, "\t", 1);
}
