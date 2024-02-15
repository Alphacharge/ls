#include "ft_ls.h"

void	merge(t_file *arr, size_t left, size_t mid, size_t right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	/* Create temporary arrays */
	t_file L[n1], R[n2];

	/* Copy data to temporary arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	/* Merge the temporary arrays back into arr[l..r] */
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (ft_strcmp(L[i].fullpath_name, R[j].fullpath_name) <= 0) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void	mergesortlist(t_file *arr, size_t left, size_t right)
{
	if (arr == NULL || left >= right)
		return ;
	
	size_t	midpoint = left + (right - left) / 2;

	ft_printf("left:%d\tmid:%d\tright:%d\n", left, midpoint, right);
	mergesortlist(arr, left, midpoint);
	mergesortlist(arr, midpoint + 1, right);

	merge(arr, left, midpoint, right);
}

void	sortfiles(t_data *data)
{
	if (data == NULL || data->tree == NULL || data->treeused == 0)
		return ;
	ft_printf("used:%d\tsize:%d\n", data->treeused, data->treesize);
	mergesortlist(data->tree, 0, data->treeused - 1);
}
