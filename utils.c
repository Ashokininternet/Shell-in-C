#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ash.h"

char *ash_read_line(void) {
    int bufsize = ASH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) { fprintf(stderr, "ash: allocation error\n"); exit(EXIT_FAILURE); }

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') { buffer[position] = '\0'; return buffer; }
        buffer[position++] = c;

        if (position >= bufsize) {
            bufsize += ASH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) { fprintf(stderr, "ash: allocation error\n"); exit(EXIT_FAILURE); }
        }
    }
}

char **ash_split_line(char *line) {
    int bufsize = ASH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) { fprintf(stderr, "ash: allocation error\n"); exit(EXIT_FAILURE); }

    token = strtok(line, ASH_TOK_DELIM);
    while (token != NULL) {
        tokens[position++] = token;
        if (position >= bufsize) {
            bufsize += ASH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) { fprintf(stderr, "ash: allocation error\n"); exit(EXIT_FAILURE); }
        }
        token = strtok(NULL, ASH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}