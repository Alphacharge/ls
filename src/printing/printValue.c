#include "ft_ls.h"

void	printValue(t_file **this, unsigned int maxValue, short link)
{
	const char	*spaces[10] = {" ", "  ", "   ", "    ", "     ", "      ", "       ", "        ", "         ", "          "};
	unsigned int	diff;
	if (link)
		diff = countDigits(maxValue) - countDigits((*this)->stat.st_nlink) + 1;
	else
		diff = countDigits(maxValue) - countDigits((*this)->stat.st_size) + 1;

	while (diff > 10){
		write(1, spaces[9], 10);
		diff -= 10;
	}
	if (diff > 0)
		write(1, spaces[diff - 1], diff);
	char *links = ft_ltoa((*this)->stat.st_nlink);
	if (links == NULL){
		ft_putstr_fd("ltoa malloc error\n", 2);
		ft_error((*this)->data, 1);
	}
	ft_putstr_fd(links, 1);
	ft_free((void **)&links);
	write(1, " ", 1);
}
