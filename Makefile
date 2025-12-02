
EXE = jogo
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCS = main.c tabuleiro.c navios.c
OBJS = $(SRCS:.c=.o)
all: $(EXE)
$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
run: $(EXE)
	./$(EXE)
clean:
	rm -f $(OBJS) $(EXE)
.PHONY: all run clean