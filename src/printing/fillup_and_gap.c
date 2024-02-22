#include "ft_ls.h"

void	fillup_and_gap(unsigned short *mask, unsigned int length, unsigned int maxlength)
{
	if (F_ISSET(*mask, F_STDOUT)){
	unsigned int spaces_needed = (TAB_WIDTH - (length % TAB_WIDTH)) % TAB_WIDTH;
	for (unsigned int i = 0; i < spaces_needed; ++i) {
		write(1, " ", 1);
		length++;
	}

	while (length < maxlength) {
		write(1, "\t", 1);
		length += TAB_WIDTH;
	}
	write(1, "\t", 1);
	}
	else
		write(1, "\n", 1);
}
