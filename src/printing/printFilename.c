#include "ft_ls.h"

void	printFilename(t_file **this)
{
	if ((*this)->fileType != _LINK)
		ft_putstr_fd((*this)->fileName, 1);
	else
	{
		char	targetPath[PATH_MAX + 1];
		int		len = 0;

		len = readlink((*this)->fullPathName, targetPath, PATH_MAX);
		if (len == -1) {
			ft_putstr_fd((*this)->fileName, 1);
			perror("readlink");
			return ;
		}
		targetPath[len] = '\0';
		if ((*this)->fileName && (*this)->data)
			ft_printf("%s -> %s", (*this)->fileName, targetPath);
	}
}
