#include "ft_ls.h"

/**
 * Handles error conditions in the ft_ls program based on the provided error code.
 * If code is 0, frees the memory allocated for the t_data structure pointed to by data.
 * If code is 1, frees the memory allocated for the t_data structure pointed to by data
 * and recursively frees the memory associated with data->folders.
 * Exits the program with EXIT_FAILURE after cleanup.
 * @param data - Pointer to the t_data structure containing program data and state.
 * @param code - Error code indicating the type of error and cleanup required.
 */
void	ft_error(t_data *data, unsigned int code)
{
	if (code == 0)
		ft_free((void**)&(data));
	else if (code == 1) {
		ft_free_tree(data->folders);
		ft_free((void**)&(data));
	}
	exit (EXIT_FAILURE);
}
