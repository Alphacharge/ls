#include "ft_ls.h"

/**
 * Sets the file type of a given t_file node based on the provided file type indicator.
 * @param node - Pointer to the t_file structure whose file type is to be set.
 * @param fileType - Unsigned char representing the file type (e.g., DT_DIR, DT_LNK, etc.).
 */
void	setFileType(t_file *node, unsigned char fileType)
{
	if (fileType == DT_DIR)
		node->fileType = _DIR;
	else if (fileType == DT_LNK)
		node->fileType = _LINK;
	else
		node->fileType = _FILE;
}
