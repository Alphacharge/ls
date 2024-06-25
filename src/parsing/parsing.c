#include "ft_ls.h"

/**
 * Parses command-line arguments to populate the data structure with options and file/directory paths.
 * @param data - Pointer to the t_data structure holding program data and flags.
 * @param argc - Number of command-line arguments.
 * @param argv - Array of strings containing command-line arguments.
 */
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
		if (data->folders == NULL){
			ft_putstr_fd("folders malloc error\n", STDERR_FILENO);
			ft_error(data, 1);
		}
		data->folders->fullPathName = ft_strdup(".");
		if (data->folders->fullPathName == NULL){
			ft_putstr_fd("folders path malloc error\n", STDERR_FILENO);
			ft_error(data, 1);
		}
		data->folders->next = NULL;
	}
	//parameter
	else
	{
		t_file	*head = NULL;
		while (argv && i < argc && j < argc && argv[i] && !isOption(argv[i]))
		{
			t_file	*new = listNew(data);
			if (new == NULL){
				ft_putstr_fd("new node malloc error\n", STDERR_FILENO);
				ft_error(data, 1);
			}
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
			if (new->fullPathName == NULL) {
				ft_putstr_fd("folders path malloc error\n", STDERR_FILENO);
				ft_error(data, 1);
			}
			data->folders = head;
		}
	}
}
