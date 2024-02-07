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

typedef enum e_type
{
	_DIR,
	_FILE,
	_LINK,
}			t_type;

typedef struct s_file
{
	t_type			type;
	// struct stat		*stat;
	// struct s_data	*data;
	struct s_file	*sub;
	struct s_file	*next;
}				t_file;

# define F_ALL			(1 << 0)	//-a
# define F_LONG			(1 << 1)	//-l
# define F_REVERSE		(1 << 2)	//-r
# define F_RECURSIVE	(1 << 3)	//-R
# define F_MTIME		(1 << 4)	//-t
# define F_ATIME		(1 << 5)	//-u
# define F_UNSORTED		(1 << 6)	//-f
# define F_GROUP		(1 << 7)	//-g
# define F_DIR			(1 << 8)	//-d
# define F_NUMID		(1 << 9)	//-n
# define F_COLOR		(1 << 10)	//-G

# define F_SET(mask, flag)		((mask) |= (flag))
# define F_CLEAR(mask, flag)	((mask) &= ~(flag))
# define F_ISSET(mask, flag)	!!((mask) & (flag))

typedef struct s_data
{
	unsigned short	*flags;
	char			**folders;
	t_file			*tree;
}				t_data;

//parsing
bool	is_option(char *argv);
void	get_options(t_data *data, char* argv);
void	parsing(t_data *data, int argc, char **argv);

//error
void	ft_error(t_data *data, unsigned int code);

//cleanup
void	ft_free(void *tofree);

void	bubblesort(char **input, int n, bool direction);

#endif
