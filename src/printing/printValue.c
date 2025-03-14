#include "ft_ls.h"

/**
 * Prints the numeric value (either file size or link count) aligned to a specified maximum width.
 * @param this - Pointer to a pointer to the t_file structure representing the file information.
 * @param maxValue - The maximum value width used for alignment.
 * @param link - Flag indicating whether to print link count (1) or file size (0).
 */
void	printValue(t_file **this, unsigned int maxValue, short link)
{
	const char		*spaces[10] = {" ", "  ", "   ", "    ", "     ", "      ", "       ", "        ", "         ", "          "};
	unsigned int	diff = 0;

	if (link)
		diff = countDigits(maxValue) - countDigits((*this)->stat.st_nlink);
	else
		diff = countDigits(maxValue) - countDigits((*this)->stat.st_size);

	while (diff > 10){
		write(STDOUT_FILENO, spaces[9], 10);
		diff -= 10;
	}
	if (diff > 0)
		write(STDOUT_FILENO, spaces[diff - 1], diff);

	if (link)
		ft_putnbr_fd((*this)->stat.st_nlink, STDOUT_FILENO);
	else
		ft_putnbr_fd((*this)->stat.st_size, STDOUT_FILENO);
}
