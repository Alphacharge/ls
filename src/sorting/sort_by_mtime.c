#include "ft_ls.h"

long	sort_by_mtime(t_file *left, t_file *right)
{
	time_t	left_time = left->stat.st_mtimespec.tv_sec;
	time_t	right_time = right->stat.st_mtimespec.tv_sec;
	if (left_time != right_time)
		return (F_ISSET(*(left)->data->flags, F_REVERSE) ? left_time < right_time : left_time > right_time);
	return 0;
}
