#include "ft_ls.h"

void	printLinks(t_file **this)
{
	const char	*spaces[10] = {" ", "  ", "   ", "    ", "     ", "      ", "       ", "        ", "         ", "          "};
	unsigned int	diff = countDigits((*this)->maxLinks) - countDigits((*this)->stat.st_nlink) + 1;

	while (diff > 10){
		write(1, spaces[9], 10);
		diff -= 10;
	}
	if (diff > 0)
		write(1, spaces[diff - 1], diff);
	char *links = ft_ltoa((*this)->stat.st_nlink);
	ft_putstr_fd(links, 1);
	ft_free((void **)&links);
	write(1, " ", 1);
}
