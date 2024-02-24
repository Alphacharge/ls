#include "ft_ls.h"

void	parsing(t_data *data, int argc, char **argv)
{
	int		i = 1;
	int		j = 0;

	while (argv && i < argc && argv[i] && isOption(argv[i]))
		getOptions(data, argv[i++]);
	//only options without parameter
	if (argv[i] == NULL)
	{
		data->folders = ft_calloc(1, sizeof(t_file));
		if (data->folders == NULL)
			ft_error(data, 1);
		data->folders->fullPathName = ft_strdup(".");
		if (data->folders->fullPathName == NULL)
			ft_error(data, 2);
		data->folders->next = NULL;
	}
	//parameter
	else
	{
		t_file	*head = NULL;
		while (argv && i < argc && j < argc && argv[i] && !isOption(argv[i]))
		{
			t_file	*new = listNew(data);
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
			new->fullPathName = ft_strdup(argv[i++]);
			if (new->fullPathName == NULL)
				ft_error(data, 2);
			data->folders = head;
		}
	}
}
