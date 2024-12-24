#include "ft_ls.h"

/**
 * Allocates and initializes a new t_file structure with default values.
 * @param data - Pointer to the t_data structure to associate with the new t_file.
 * @return - Returns a pointer to the newly allocated t_file structure,
 *           or NULL if memory allocation fails.
 */
t_file	*listNew(t_data *data)
{
	t_file	*new = malloc(1 * sizeof(t_file));
	if (new == NULL)
		return NULL;
	new->next = NULL;
	new->fileName = NULL;
	new->lowercaseName = NULL;
	new->fullPathName = NULL;
	new->data = data;
	new->fileNameLength = 0;
	new->maxFileNameLength = 0;
	new->maxLinks = 0;
	new->fileType = _NONE;
	new->userName = NULL;
	new->userLength = 0;
	new->maxUserLength = 0;
	new->groupName = NULL;
	new->groupLength = 0;
	new->maxGroupLength = 0;
	return new;
}
