#include "ft_ls.h"

void	printBytes(t_file **this)
{
	unsigned int maxChars = countDigits((*this)->maxBytes);
	unsigned int thisChars = countDigits((*this)->stat.st_size);

	write(1, " ", 1);
	while (thisChars++ < maxChars)
		write(1, " ", 1);
	char *links = ft_ltoa((*this)->stat.st_size);
	ft_putstr_fd(links, 1);
	ft_free((void **)&links);
	write(1, " ", 1);
}
