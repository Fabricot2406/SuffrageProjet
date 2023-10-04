CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = Suffrage

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

.PHONY: all clean
