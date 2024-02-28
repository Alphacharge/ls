#include "ft_ls.h"

void	printUser(t_file **this)
{
	unsigned int	i = (*this)->userLength;
	while (i++ < (*this)->maxUserLength)
		write(1, " ", 1);
	ft_putstr_fd((*this)->userName, 1);
	write(1, " ", 1);
}
