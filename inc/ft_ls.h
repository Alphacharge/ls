#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <unistd.h>	//write, readlink
# include <dirent.h>	//opendir, readdir, closedir
# include <sys/stat.h>	//stat, lstat
# include <sys/types.h>	//
# include <pwd.h>		//getpwuid
# include <grp.h>		//getgrgid
# include <stdlib.h>	//malloc, free, exit
# include <stdio.h>		//perror, strerror
# include <time.h>		//time, ctime
# include <sys/xattr.h>	//listxattr

# ifdef __linux__
#  define SYSTEM 0
#  define OFFSET dir->d_off
# endif

# ifdef __APPLE__
#  define SYSTEM 1
#  define OFFSET dir->d_seekoff
# endif

void	bubblesort(char **input, int n);

#endif
