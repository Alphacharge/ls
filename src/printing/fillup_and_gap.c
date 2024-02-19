#include "ft_ls.h"

void	fillup_and_gap(unsigned int length, unsigned int maxlength)
{
	unsigned int spaces_needed = (TAB_WIDTH - (length % TAB_WIDTH)) % TAB_WIDTH;

	for (int i = 0; i < spaces_needed; ++i) {
		write(1, " ", 1);
		length++;
	}

	while (length < maxlength) {
		write(1, "\t", 1);
		length += TAB_WIDTH;
	}
	write(1, "\t", 1);
}
