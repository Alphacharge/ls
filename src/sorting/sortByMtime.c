#include "ft_ls.h"

/**
 * Compares two t_file structures based on their modification time if the F_MTIME flag is set in data->flags,
 * otherwise compares alphabetically.
 * @param left - Pointer to the first t_file structure to compare.
 * @param right - Pointer to the second t_file structure to compare.
 * @return A negative value if left should precede right, a positive value if right should precede left,
 *         and zero if they are considered equal according to the sorting criteria.
 */
long	sortByMtime(t_file *left, t_file *right)
{
	time_t	leftTimeSec = left->TIME_SEC;
	time_t	rightTimeSec = right->TIME_SEC;
	if (leftTimeSec != rightTimeSec)
		return (F_ISSET(*(left)->data->flags, F_REVERSE) ? leftTimeSec < rightTimeSec : leftTimeSec > rightTimeSec);

	time_t	leftTimeNsec = left->TIME_NSEC;
	time_t	rightTimeNsec = right->TIME_NSEC;
	if (leftTimeNsec != rightTimeNsec)
		return (F_ISSET(*(left)->data->flags, F_REVERSE) ? leftTimeNsec < rightTimeNsec : leftTimeNsec > rightTimeNsec);

	return SORT_BY_ALPHA(left, right);
}
