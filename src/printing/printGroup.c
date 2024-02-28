#include "ft_ls.h"

void	printGroup(t_file **this)
{
	unsigned int	i = (*this)->groupLength;
	write(1, " ", 1);
	while (i++ < (*this)->maxGroupLength)
		write(1, " ", 1);
	ft_putstr_fd((*this)->grp->gr_name, 1);
	write(1, " ", 1);
}
