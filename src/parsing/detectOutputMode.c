#include "ft_ls.h"

/**
 * Detects the output mode of the program based on the file descriptor of stdout.
 * @param data - Pointer to the data structure containing program flags.
 */
void	detectOutputMode(t_data *data)
{
	struct stat statbuf;

	if (fstat(STDOUT_FILENO, &statbuf) == -1) {
		perror("fstat");
		ft_error(data, 1);
	}

	if (S_ISREG(statbuf.st_mode)) {
		// Output is redirected to a regular file
		F_CLEAR(*data->flags, F_STDOUT);
	} else if (S_ISFIFO(statbuf.st_mode)) {
		// Output is redirected to a pipe
		F_CLEAR(*data->flags, F_STDOUT);
	} else {
		// Output is going to the terminal
		F_SET(*data->flags, F_STDOUT);
	}
}
