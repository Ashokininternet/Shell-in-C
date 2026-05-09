CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -g
TARGET  = ash
SRCS    = shell.c builtins.c core.c utils.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c ash.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)