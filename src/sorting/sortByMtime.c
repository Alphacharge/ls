#include "ft_ls.h"

long	sortByMtime(t_file *left, t_file *right)
{
	time_t	leftTime = left->TIME;
	time_t	rightTime = right->TIME;
	if (leftTime != rightTime)
		return (F_ISSET(*(left)->data->flags, F_REVERSE) ? leftTime < rightTime : leftTime > rightTime);
	return SORT_BY_ALPHA(left, right);
}
