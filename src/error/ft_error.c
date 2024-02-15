#include "ft_ls.h"

void	ft_error(t_data *data, unsigned int code)
{
	switch(code) {
		case 0:
			ft_printf("data malloc error\n");
			exit (++code);
		case 1:
			ft_free(data);
			ft_printf("folders array malloc error\n");
			exit (++code);
		case 2:
			ft_free_array((void **)data->folders);
			ft_free(data);
			ft_printf("folder malloc error\n");
			exit (++code);
		case 3:
			ft_free_tree(data);
			ft_free_array((void **)data->folders);
			ft_free(data);
			ft_printf("tree creation malloc error\n");
			exit (++code);
		case 4:
			ft_free_tree(data);
			ft_free_array((void **)data->folders);
			ft_free(data);
			ft_printf("No such file or directory.\n");
			exit (++code);
		case 5:
			ft_free_tree(data);
			ft_free_array((void **)data->folders);
			ft_free(data);
			ft_printf("couldn't join path.\n");
			exit (++code);
		case 6:
			ft_free_tree(data);
			ft_free_array((void **)data->folders);
			ft_free(data);
			ft_printf("opendir failed.\n");
			exit (++code);
		case 7:
			ft_free_tree(data);
			ft_free_array((void **)data->folders);
			ft_free(data);
			ft_printf("buffer overflow.\n");
			exit (++code);
	}
}
