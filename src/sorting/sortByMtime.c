#include "ft_ls.h"

/**
 * Compares two t_file structures based on their modification time if the F_MTIME flag is set in data->flags,
 * otherwise compares alphabetically based on fullPathName.
 * @param left - Pointer to the first t_file structure to compare.
 * @param right - Pointer to the second t_file structure to compare.
 * @return A negative value if left should precede right, a positive value if right should precede left,
 *         and zero if they are considered equal according to the sorting criteria.
 */
long	sortByMtime(t_file *left, t_file *right)
{
	time_t	leftTime = left->TIME_NSEC;
	time_t	rightTime = right->TIME_NSEC;
	if (leftTime != rightTime)
		return (F_ISSET(*(left)->data->flags, F_REVERSE) ? leftTime < rightTime : leftTime > rightTime);
	return SORT_BY_ALPHA(left, right);
}
