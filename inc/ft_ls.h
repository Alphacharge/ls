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

/*----------------------------------------------------------------------------*/
/*--------------------------SYSTEM SETTINGS-----------------------------------*/
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/*--------------------------DATA STRUCTURES-----------------------------------*/
/*----------------------------------------------------------------------------*/
typedef enum e_type
{
	_NONE,
	_DIR,
	_FILE,
	_LINK,
}			t_type;

typedef struct s_file
{
	t_type			fileType;
	char			*fileName;
	char			*fullPathName;
	unsigned int	fileNameLength;
	unsigned int	maxFileNameLength;
	unsigned int	maxLinks;
	struct stat		stat;
	struct s_data	*data;
	struct s_file	*next;
}				t_file;

typedef struct s_data
{
	unsigned short	*flags;
	t_file			*folders;
}				t_data;

/*----------------------------------------------------------------------------*/
/*--------------------------CUSTOM DEFINITIONS--------------------------------*/
/*----------------------------------------------------------------------------*/
# define TAB_WIDTH 4
# define DEBUG 0

/*----------------------------------------------------------------------------*/
/*-----------------------------OPTIONS BITMASK--------------------------------*/
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/*-----------------------------SORTING MACROS---------------------------------*/
/*----------------------------------------------------------------------------*/
# define SORT_BY_ALPHA(left, right) \
	(F_ISSET(*(left)->data->flags, F_REVERSE) \
	? ft_strcmp((left)->fullPathName, (right)->fullPathName) > 0 \
	: ft_strcmp((left)->fullPathName, (right)->fullPathName) < 0 )

# define SORTDIR(left, right) \
	((F_ISSET(*(left)->data->flags, F_MTIME)) \
	? (sortByMtime(left, right)) \
	: (SORT_BY_ALPHA(left, right)))

/*----------------------------------------------------------------------------*/
/*-------------------------FUNCTION PROTOTYPES--------------------------------*/
/*----------------------------------------------------------------------------*/

//parsing
bool			isOption(char *argv);
void			getOptions(t_data *data, char* argv);
bool			isDotfile(char *filename);
bool			isSpecialDir(char *filename);
void			setFileType(t_file *node, unsigned char type);
void			detectOutputMode(t_data *data);
unsigned int	countDigits(unsigned int digit);

void			parsing(t_data *data, int argc, char **argv);
void			loop(t_data **data, t_file **treelvl, char *path, DIR *ref);

t_file			*listNew(t_data *data);
// unsigned int	listSize(t_file *tree);
// t_file			*listLast(t_file *tree);
// void			listUpdateMaxlength(t_file *head, unsigned int length);

//error
void	ft_error(t_data *data, unsigned int code);

//cleanup
void	ft_free(void **tofree);
void	ft_free_tree(t_file	*tree);

//printing
void	insertPadding(unsigned int length, unsigned int maxlength);
// void	print_tree(t_file *tree, int lvl);
// void	print_inline_tree(t_file *tree);
void	printTreelvl(t_file **tree);
void	printLongTreelvl(t_file **tree);
void	printLinks(t_file *this);
// void	print_debug_tree(t_file *tree, int lvl);
// void	print_array(char **array);
// bool	print_dotfile(unsigned short *flags, char *filename);

//sorting
long	sortByMtime(t_file *left, t_file *right);
// void	bubblesort(char **input, int n, bool direction);
t_file	*merge(t_file *left, t_file *right);
t_file	*splitList(t_file *head);
t_file	*mergesortFileList(t_file *tree);

#endif

//                 OK
// -a              OK
// -t              OK
// -aR             OK
// -ar             OK
// -at             OK
// -aRt            OK
// -art            OK