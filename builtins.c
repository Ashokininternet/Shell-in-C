#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include "ash.h"

char *builtin_str[] = { "cd", "help", "exit", "ls", "rm", "make"};

int (*builtin_func[])(char **) = {
    &ash_cd,
    &ash_help,
    &ash_exit,
    &ash_ls,
    &ash_rm,
    &ash_make
};

int ash_num_builtins(void) {
    return sizeof(builtin_str) / sizeof(char *);
}

int ash_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "ash: expected argument to \"cd\"\n");
    } else if (chdir(args[1]) != 0) {
        perror("ash");
    }
    return 1;
}

int ash_help(char **args) {
    (void)args;
    printf("Type program names and arguments, and hit enter.\n");
    printf("Built-in commands:\n");
    for (int i = 0; i < ash_num_builtins(); i++)
        printf("  %s\n", builtin_str[i]);
    return 1;
}

int ash_exit(char **args) {
    (void)args;
    return 0;
}

int ash_ls(char **args) {
    const char *path = (args[1] == NULL) ? "." : args[1];
    DIR *dr = opendir(path);
    if (dr == NULL) { perror("ash"); return 1; }

    struct dirent *de;
    while ((de = readdir(dr)) != NULL)
        if (de->d_name[0] != '.')
            printf("%s  ", de->d_name);
    printf("\n");
    closedir(dr);
    return 1;
}

int ash_rm(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "ash: expected argument to \"rm\"\n");
    } else if (unlink(args[1]) != 0) {
        perror("ash");
    }
    return 1;
}
int ash_make(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "ash: expected argument to \"touch\"\n");
        return 1;
    }

    for (int i = 1; args[i] != NULL; i++) {
        int fd = open(args[i], O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            perror("ash: touch");
            continue;
        }
        close(fd);

        if (utime(args[i], NULL) != 0) {
            perror("ash: touch");
        }
    }
    return 1;
}