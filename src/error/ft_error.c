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
		// case 3:
		// 	while (data && data->folders)
		// 		ft_free(data->folders++);
		// 	ft_free(data);
		// 	ft_printf("folder malloc error\n");
		// 	exit (++code);
	}
}
