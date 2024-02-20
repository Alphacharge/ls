#include "ft_ls.h"

long	sort_by_mtime(t_file *left, t_file *right)
{
	time_t	left_time = left->TIME;
	time_t	right_time = right->TIME;
	if (left_time != right_time)
		return (F_ISSET(*(left)->data->flags, F_REVERSE) ? left_time < right_time : left_time > right_time);
	return SORT_BY_ALPHA(left, right);
}
