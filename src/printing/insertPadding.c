#include "ft_ls.h"

void	insertPadding(unsigned int fileNameLength, unsigned int maxFileNameLength)
{
	unsigned int spaces_needed = (TAB_WIDTH - (fileNameLength % TAB_WIDTH)) % TAB_WIDTH;
	for (unsigned int i = 0; i < spaces_needed; ++i) {
		write(1, " ", 1);
		fileNameLength++;
	}

	while (fileNameLength < maxFileNameLength) {
		write(1, "\t", 1);
		fileNameLength += TAB_WIDTH;
	}
	write(1, "\t", 1);
}
