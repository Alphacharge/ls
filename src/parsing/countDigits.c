#include "ft_ls.h"

unsigned int	countDigits(unsigned int digit)
{
	unsigned int	n;

	n = 0;
	if (digit == 0)
		return (1);
	while (digit != 0)
	{
		digit = digit / 10;
		n++;
	}
	return (n);
}
