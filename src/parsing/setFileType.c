#include "ft_ls.h"

void	setFileType(t_file *node, unsigned char type)
{
	if (type == DT_DIR)
		node->type = _DIR;
	else if (type == DT_LNK)
		node->type = _LINK;
	else
		node->type = _FILE;
}
