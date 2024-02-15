#include "ft_ls.h"

void	fillup_and_gap(unsigned int length)
{
	while (length++ % 4)
		ft_printf(" ");
	ft_printf("\t");
}
