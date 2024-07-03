#include "ft_ls.h"

/**
 * Frees the memory pointed to by the pointer **tofree and sets it to NULL to prevent
 * dangling pointers.
 * @param tofree - Double pointer to dynamically allocated memory.
 */
void	ft_free(void **tofree)
{
	free(*tofree);
	*tofree = NULL;
}
