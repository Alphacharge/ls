#include "ft_ls.h"

/**
 * Prints the filename or filename followed by the symlink target path if the file is a symbolic link.
 * @param this - Double pointer to the t_file structure representing the file information.
 */
void	printFilename(t_file **this)
{
	if ((*this)->fileType != _LINK)
		ft_putstr_fd((*this)->fileName, STDOUT_FILENO);
	else
	{
		char	targetPath[PATH_MAX + 1];
		int		len = 0;

		len = readlink((*this)->fullPathName, targetPath, PATH_MAX);
		if (len == -1) {
			ft_putstr_fd((*this)->fileName, STDERR_FILENO);
			perror("readlink");
			return ;
		}
		targetPath[len] = '\0';
		if ((*this)->fileName)
			ft_printf("%s -> %s", (*this)->fileName, targetPath);
	}
}
