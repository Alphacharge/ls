#include "ft_ls.h"

t_file	*new_node(t_data *data)
{
	t_file	*new = malloc(1 * sizeof(t_file));
	if (new == NULL)
		return NULL;
	new->next = NULL;
	new->sub = NULL;
	new->name = NULL;
	new->path = NULL;
	new->fullpath_name = NULL;
	new->data = data;
	new->length = 0;
	new->maxlength = 0;
	new->listsize = 0;
	new->type = _NONE;
	return new;
}
