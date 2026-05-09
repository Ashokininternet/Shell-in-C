#ifndef ASH_H
#define ASH_H

#define ASH_RL_BUFSIZE  1024
#define ASH_TOK_BUFSIZE 64
#define ASH_TOK_DELIM   " \t\r\n\a"

/* ── builtins ── */
int ash_cd(char **args);
int ash_help(char **args);
int ash_exit(char **args);
int ash_ls(char **args);
int ash_rm(char **args);
int ash_make(char **args);
int ash_num_builtins(void);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

/* ── core ── */
int ash_launch(char **args);
int ash_execute(char **args);
void ash_loop(void);

/* ── utils ── */
char  *ash_read_line(void);
char **ash_split_line(char *line);

#endif