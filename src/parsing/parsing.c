#include "ft_ls.h"

void	parsing(t_data *data, int argc, char **argv)
{
	int		i = 1;
	int		j = 0;

	while (argv && i < argc && argv[i] && is_option(argv[i]))
		get_options(data, argv[i++]);
	//only options without parameter
	if (argv[i] == NULL)
	{
		data->folders = malloc(2 * sizeof(char*));
		if (data->folders == NULL)
			ft_error(data, 1);
		data->folders[0] = ft_strdup(".");
		if (data->folders[0] == NULL)
			ft_error(data, 2);
		data->folders[1] = NULL;
	}
	//parameter
	else
	{
		data->folders = malloc(argc * sizeof(char*));
		if (data->folders == NULL)
			ft_error(data, 1);
		data->folders[argc - 1] = NULL;
		while (argv && i < argc && j < argc && argv[i] && !is_option(argv[i]))
		{
			data->folders[j] = ft_strdup(argv[i++]);
			if (data->folders[j++] == NULL)
				ft_error(data, 2);
		}
	}
}
