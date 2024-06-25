#include "ft_ls.h"

/**
 * Counts the number of digits in a given unsigned integer.
 * @param digit - The unsigned integer to count digits of.
 * @return - The number of digits in the input integer.
 */
unsigned int	countDigits(unsigned int digit)
{
	unsigned int	n;

	n = 0;
	if (digit < 10)
		return (1);
	while (digit != 0)
	{
		digit = digit / 10;
		n++;
	}
	return (n);
}
