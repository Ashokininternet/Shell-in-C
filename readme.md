# Shell-in-C
A basic Unix shell implementation written in C. Demonstrates how a 
command-line interface handles user input, process creation, and 
execution using system calls.

## Features

**Command Execution:** Executes external programs by forking child processes.

**Built-in Commands:**
- `cd` — Change the current working directory.
- `help` — Display available built-in commands.
- `exit` — Terminate the shell session.
- `ls` — List files in the current or specified directory.
- `rm` — Remove a specified file.
- `make` — Create a new file or update timestamps of an existing one.

## Prerequisites
- A C compiler (`gcc`)
- A Linux or Unix-like environment

## Building

```bash
make
```

To clean build artifacts:
```bash
make clean
```

## Status
Under active development. More commands will be added.