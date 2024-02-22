#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include "colors.h"
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
// #  define OFFSET dir->d_off
#  define NAMELENGTH ft_strlen(dir->d_name)
#  define TIME stat.st_mtime
# endif

# ifdef __APPLE__
#  define SYSTEM 1
// #  define OFFSET dir->d_seekoff
#  define NAMELENGTH dir->d_namlen
#  define TIME stat.st_mtimespec.tv_sec
# endif

typedef enum e_type
{
	_NONE,
	_DIR,
	_FILE,
	_LINK,
}			t_type;

typedef struct s_file
{
	t_type			type;
	char			*path;
	char			*name;
	char			*fullpath_name;
	unsigned int	length;
	unsigned int	maxlength;
	unsigned int	listsize;
	struct stat		stat;
	struct s_data	*data;
	struct s_file	*sub;
	struct s_file	*next;
}				t_file;
# define TAB_WIDTH 4

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
# define F_FOLDERSORT	(1 << 11)	//flag to sort args
# define F_STDOUT		(1 << 12)	//flag to recognize output 1 stdout 0 pipe or file

# define F_SET(mask, flag)		((mask) |= (flag))
# define F_CLEAR(mask, flag)	((mask) &= ~(flag))
# define F_ISSET(mask, flag)	!!((mask) & (flag))

# define SORT_BY_ALPHA(left, right) \
	(F_ISSET(*(left)->data->flags, F_REVERSE) \
	? ft_strcmp((left)->fullpath_name, (right)->fullpath_name) > 0 \
	: ft_strcmp((left)->fullpath_name, (right)->fullpath_name) < 0 )

# define SORTDIR(left, right) \
	((F_ISSET(*(left)->data->flags, F_MTIME)) \
	? (sort_by_mtime(left, right)) \
	: (SORT_BY_ALPHA(left, right)))

typedef struct s_data
{
	unsigned short	*flags;
	t_file			*folders;
	// DIR				*dirref;
	t_file			*tree;
}				t_data;

//parsing
bool			isOption(char *argv);
bool			isDotfile(char *filename);
bool			isSpecialDir(char *filename);
void			getOptions(t_data *data, char* argv);
void			setFileType(t_file *node, unsigned char type);
void			detectOutputMode(t_data *data);

void			parsing(t_data *data, int argc, char **argv);
void			loop(t_data *data, t_file *treelvl, char *path, DIR *ref);

t_file			*listNew(t_data *data);
unsigned int	listSize(t_file *tree);
t_file			*listLast(t_file *tree);
void			listUpdateMaxlength(t_file *head, unsigned int length);

//error
void	ft_error(t_data *data, unsigned int code);

//cleanup
void	ft_free(void **tofree);
void	ft_free_tree(t_file	*tree);

//printing
void	fillup_and_gap(unsigned short *mask, unsigned int length, unsigned int maxlength);
// void	print_tree(t_file *tree, int lvl);
// void	print_inline_tree(t_file *tree);
void	print_treelvl(t_file *tree);
// void	print_debug_tree(t_file *tree, int lvl);
// void	print_array(char **array);
// bool	print_dotfile(unsigned short *flags, char *filename);

//sorting
long	sort_by_mtime(t_file *left, t_file *right);
void	bubblesort(char **input, int n, bool direction);
t_file	*merge(t_file *left, t_file *right);
t_file	*splitlist(t_file *head);
t_file	*mergesortlist(t_file *tree);

#endif

// rbetz@2-G-6:8_ls$./ft_ls -t src/ inc
// inc:
// ft_ls.h         colors.h

// src/:
// main.c          parsing         loop.c          cleanup         printing        sorting         error           options
// rbetz@2-G-6:8_ls$./ft_ls -tr src/ inc
// inc:
// colors.h        ft_ls.h 

// src/:
// options         error           sorting         printing        cleanup         loop.c          parsing         main.c  
// rbetz@2-G-6:8_ls$./ft_ls src/ inc
// inc:
// colors.h        ft_ls.h

// src/:
// cleanup         error           loop.c          main.c          options         parsing         printing        sorting
// rbetz@2-G-6:8_ls$./ft_ls -r src/ inc
// inc:
// ft_ls.h         colors.h

// src/:
// sorting         printing        parsing         options         main.c          loop.c          error           cleanup 
// rbetz@2-G-6:8_ls$ls -t src/ inc
// src/:
// main.c          parsing         loop.c          cleanup         printing        sorting         error           options

// inc:
// ft_ls.h         colors.h
// rbetz@2-G-6:8_ls$ls -tr src/ inc
// inc:
// colors.h        ft_ls.h

// src/:
// options         error           sorting         printing        cleanup         loop.c          parsing         main.c
// rbetz@2-G-6:8_ls$ls src/ inc
// inc:
// colors.h        ft_ls.h

// src/:
// cleanup         error           loop.c          main.c          options         parsing         printing        sorting
// rbetz@2-G-6:8_ls$ls -r src/ inc
// src/:
// sorting         printing        parsing         options         main.c          loop.c          error           cleanup

// inc:
// ft_ls.h         colors.h