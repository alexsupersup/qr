CC=gcc
CFLAGS=-Wall -Werror
OUTPUT=$@

%: %.c
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT)