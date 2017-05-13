CC = g++
CFLAGS = -Wall
OBJ = main.o game_state_class.o ai_class.o

all: main

main.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONT: clean

clean:
	rm -f *.o main *.out
