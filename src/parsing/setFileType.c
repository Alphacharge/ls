#include "ft_ls.h"

void	setFileType(t_file *node, unsigned char fileType)
{
	if (fileType == DT_DIR)
		node->fileType = _DIR;
	else if (fileType == DT_LNK)
		node->fileType = _LINK;
	else
		node->fileType = _FILE;
}
