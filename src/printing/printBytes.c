#include "ft_ls.h"

void	printBytes(t_file **this)
{
	const char	*spaces[10] = {" ", "  ", "   ", "    ", "     ", "      ", "       ", "        ", "         ", "          "};
	unsigned int	diff = countDigits((*this)->maxBytes) - countDigits((*this)->stat.st_size) + 1;

	while (diff > 10){
		write(1, spaces[9], 10);
		diff -= 10;
	}
	if (diff > 0)
		write(1, spaces[diff - 1], diff);
	// unsigned int maxChars = countDigits((*this)->maxBytes);
	// unsigned int thisChars = countDigits((*this)->stat.st_size);

	// write(1, " ", 1);
	// while (thisChars++ < maxChars)
	// 	write(1, " ", 1);
	char *links = ft_ltoa((*this)->stat.st_size);
	ft_putstr_fd(links, 1);
	ft_free((void **)&links);
	write(1, " ", 1);
}
