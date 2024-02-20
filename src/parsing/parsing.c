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
		data->folders = ft_calloc(1, sizeof(t_file));
		if (data->folders == NULL)
			ft_error(data, 1);
		data->folders->fullpath_name = ft_strdup(".");
		if (data->folders->fullpath_name == NULL)
			ft_error(data, 2);
		data->folders->next = NULL;
	}
	//parameter
	else
	{
		t_file	*head = NULL;
		while (argv && i < argc && j < argc && argv[i] && !is_option(argv[i]))
		{
			t_file	*new = new_node(data);
			if (new == NULL)
				ft_error(data, 2);
			if (head == NULL)
				head = new;
			else
			{
				t_file	*last = head;
				while (last && last->next)
					last = last->next;
				last->next = new;
			}
			new->fullpath_name = ft_strdup(argv[i++]);
			if (new->fullpath_name == NULL)
				ft_error(data, 2);
			data->folders = head;
		}
	}
}
