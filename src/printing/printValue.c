#include "ft_ls.h"

void	printValue(t_file **this, unsigned int maxValue, short link)
{
	const char		*spaces[10] = {" ", "  ", "   ", "    ", "     ", "      ", "       ", "        ", "         ", "          "};
	unsigned int	diff = 0;
	char			*value = NULL;

	if (link) {
		diff = countDigits(maxValue) - countDigits((*this)->stat.st_nlink) + 1;
		value = ft_ltoa((*this)->stat.st_nlink);
	}
	else
	{
		diff = countDigits(maxValue) - countDigits((*this)->stat.st_size) + 1;
		value = ft_ltoa((*this)->stat.st_size);
	}
	if (value == NULL){
		ft_putstr_fd("ltoa malloc error\n", 2);
		ft_error((*this)->data, 1);
	}

	while (diff > 10){
		write(1, spaces[9], 10);
		diff -= 10;
	}
	if (diff > 0)
		write(1, spaces[diff - 1], diff);

	ft_putstr_fd(value, 1);
	ft_free((void **)&value);
	write(1, " ", 1);
}
