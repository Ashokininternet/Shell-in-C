#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ash.h"

int ash_launch(char **args)
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
            perror("ash");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("ash");
    }
    else
    {
        pid_t wpid;
        do
        {
            (void)waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int ash_execute(char **args)
{
    if (args[0] == NULL)
        return 1;
    for (int i = 0; i < ash_num_builtins(); i++)
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    return ash_launch(args);
}

void ash_loop(void)
{
    char *line;
    char **args;
    int status;
    do
    {
        printf("ash -> ");
        line = ash_read_line();
        args = ash_split_line(line);
        status = ash_execute(args);
        free(line);
        free(args);
    } while (status);
}