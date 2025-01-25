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

	//parse all options
	while (argv && i < argc && argv[i] && isOption(argv[i])) {
		getOptions(data, argv[i]);
		++i;
	}

	//parse all parameters
	t_file	*head = NULL;
	t_file	*tail = NULL;
	while (argv && i < argc && argv[i])
	{
		t_file	*new = listNew(data);
		if (new == NULL){
			ft_putstr_fd("new node malloc error\n", STDERR_FILENO);
			ft_error(data, 1);
		}
		new->fullPathName = ft_strdup(argv[i]);
		new->fileName = ft_strdup(new->fullPathName);
		new->lowercaseName = ft_strlower(ft_strdup(new->fullPathName));
		if (new->fullPathName == NULL || new->lowercaseName == NULL) {
			ft_putstr_fd("folders path malloc error\n", STDERR_FILENO);
			ft_error(data, 1);
		}
		if (head == NULL) {
			head = new;
			data->folders = head;
			tail = new;
		} else {
			tail->next = new;
			tail = new;
		}
		++i;
	}

	//set . if no parameter is given
	if (data->folders == NULL)
	{
		data->folders = listNew(data);
		if (data->folders == NULL){
			ft_putstr_fd("folders malloc error\n", STDERR_FILENO);
			ft_error(data, 1);
		}
		data->folders->fullPathName = ft_strdup(".");
		data->folders->lowercaseName = ft_strlower(ft_strdup("."));
		if (data->folders->fullPathName == NULL || data->folders->lowercaseName == NULL){
			ft_putstr_fd("folders path malloc error\n", STDERR_FILENO);
			ft_error(data, 1);
		}
		data->folders->next = NULL;
	}
}
