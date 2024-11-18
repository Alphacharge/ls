#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void list_dir(const char *path, int show_all, int long_format, int reverse, int comma_separated, int recursive);

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        handle_error("malloc");
    }
    return ptr;
}

void print_permissions(mode_t mode) {
    char perms[11] = "----------";
    perms[0] = S_ISDIR(mode) ? 'd' : '-';
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';
    printf("%s", perms);
}

void print_file_info(const char *path, const struct dirent *entry, int long_format) {
    if (long_format) {
        struct stat statbuf;
        char *fullpath = xmalloc(strlen(path) + strlen(entry->d_name) + 2);
        sprintf(fullpath, "%s/%s", path, entry->d_name);
        if (stat(fullpath, &statbuf) == -1) {
            free(fullpath);
            handle_error("stat");
        }

        print_permissions(statbuf.st_mode);
        printf(" %ld", (long) statbuf.st_nlink);
        struct passwd *pwd = getpwuid(statbuf.st_uid);
        struct group *grp = getgrgid(statbuf.st_gid);
        if (pwd) {
            printf(" %s", pwd->pw_name);
        } else {
            printf(" %d", statbuf.st_uid);
        }
        if (grp) {
            printf(" %s", grp->gr_name);
        } else {
            printf(" %d", statbuf.st_gid);
        }
        printf(" %5ld", (long) statbuf.st_size);

        char timebuf[64];
        struct tm *tm_info = localtime(&statbuf.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
        printf(" %s", timebuf);

        printf(" %s\n", entry->d_name);
        free(fullpath);
    } else {
        printf("%s\n", entry->d_name);
    }
}

int compare(const struct dirent **a, const struct dirent **b) {
    return strcasecmp((*a)->d_name, (*b)->d_name);
}

void list_dir(const char *path, int show_all, int long_format, int reverse, int comma_separated, int recursive) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, compare);
    if (n == -1) {
        handle_error("scandir");
    }

    int start = 0;
    int end = n;
    int step = 1;
    if (reverse) {
        start = n - 1;
        end = -1;
        step = -1;
    }

    for (int i = start; i != end; i += step) {
        if (!show_all && namelist[i]->d_name[0] == '.') {
            free(namelist[i]);
            continue;
        }
        if (comma_separated && i != start) {
            printf(", ");
        }
        print_file_info(path, namelist[i], long_format);
        free(namelist[i]);
    }
    free(namelist);

    if (recursive) {
        n = scandir(path, &namelist, NULL, compare);
        if (n == -1) {
            handle_error("scandir");
        }
        for (int i = 0; i < n; i++) {
            if (namelist[i]->d_type == DT_DIR &&
                (show_all || namelist[i]->d_name[0] != '.') &&
                strcmp(namelist[i]->d_name, ".") != 0 &&
                strcmp(namelist[i]->d_name, "..") != 0) {
                char *subdir = xmalloc(strlen(path) + strlen(namelist[i]->d_name) + 2);
                sprintf(subdir, "%s/%s", path, namelist[i]->d_name);
                printf("\n%s:\n", subdir);
                list_dir(subdir, show_all, long_format, reverse, comma_separated, recursive);
                free(subdir);
            }
            free(namelist[i]);
        }
        free(namelist);
    }
}

int main(int argc, char *argv[]) {
    int show_all = 0, long_format = 0, reverse = 0, comma_separated = 0, recursive = 0;
    int opt;

    while ((opt = getopt(argc, argv, "alrmR")) != -1) {
        switch (opt) {
            case 'a': show_all = 1; break;
            case 'l': long_format = 1; break;
            case 'r': reverse = 1; break;
            case 'm': comma_separated = 1; break;
            case 'R': recursive = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-alrmR] [path...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        list_dir(".", show_all, long_format, reverse, comma_separated, recursive);
    } else {
        for (int i = optind; i < argc; i++) {
            printf("%s:\n", argv[i]);
            list_dir(argv[i], show_all, long_format, reverse, comma_separated, recursive);
            if (i < argc - 1) {
                printf("\n");
            }
        }
    }

    return 0;
}
