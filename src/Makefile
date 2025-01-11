CC=gcc
CFLAGS=-Wall
EXEC=game
INCLUDE=-I../include -I/usr/include/SDL2
LIB=-L/usr/lib/ -L.
SRC=entites.c graphique.c jeu.c
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): main.c libmodulesjeu.a
	$(CC) $(CFLAGS) $(INCLUDE) $(LIB) -o $@ main.c -lmodulesjeu -lSDL2 -lSDL2_ttf

libmodulesjeu.a: $(OBJ)
	ar cr $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

.PHONY: clean
clean:
	rm *.o libmodulesjeu.a game
