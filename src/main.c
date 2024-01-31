#include "ft_ls.h"

int main(int argc, char** argv) {
	char* folder;
	if (argc < 2)
		folder = ".";
	else {
		bubblesort(argv + 1, argc - 1);
		folder = argv[1];
	}
	for (int i = 1; folder != NULL; ++i, folder = argv[i]){
		DIR* ref = opendir(folder);
		if (ref == NULL)
			return 1;
		if (argc > 1)
			ft_printf("%s:\n", folder);
		for (struct dirent* dir = readdir(ref); dir != NULL; dir = readdir(ref)) {
			if (SYSTEM && dir && OFFSET < 3)
				continue;
			// else if (!SYSTEM && dir && dir->d_off < 3)
			// 	continue;
			ft_printf("%d,\t%s\t%d\n", dir->d_ino, dir->d_name, OFFSET);
		}
	}

	return 0;
}