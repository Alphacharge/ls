#include "ft_ls.h"

void	detectOutputMode(t_data *data)
{
	int	fd = 1;
	struct stat statbuf;

	if (fstat(fd, &statbuf) == -1) {
		perror("fstat");
		exit(EXIT_FAILURE);
		//needs freeing
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
