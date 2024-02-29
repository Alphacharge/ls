#include "ft_ls.h"

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
