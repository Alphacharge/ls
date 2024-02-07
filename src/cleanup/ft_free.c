#include "ft_ls.h"

void	ft_free(void *tofree)
{
	free(tofree);
	tofree = NULL;
}
