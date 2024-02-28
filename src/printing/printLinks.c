#include "ft_ls.h"

void	printLinks(t_file **this)
{
	unsigned int maxChars = countDigits((*this)->maxLinks);
	unsigned int thisChars = countDigits((*this)->stat.st_nlink);

	write(1, " ", 1);
	// ft_printf("this:%d,max:%d\n", thisChars, maxChars);
	while (thisChars++ < maxChars)
		write(1, " ", 1);
	// ft_printf("this:%d,max:%d\n", thisChars, maxChars);
	char *links = ft_ltoa((*this)->stat.st_nlink);
	ft_putstr_fd(links, 1);
	ft_free((void **)&links);
	write(1, " ", 1);
}
