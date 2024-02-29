#include "ft_ls.h"

void	printUserGroup(unsigned int length, unsigned int maxLength, char *value)
{
	unsigned int	i = length;
	write(1, " ", 1);
	while (i++ < maxLength)
		write(1, " ", 1);
	ft_putstr_fd(value, 1);
	write(1, " ", 1);
}