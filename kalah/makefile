CC = g++
CFLAGS = -O3
OBJ = kalahMain.o kalah.o ai.o

all: main.out

main.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONT: clean

clean:
	rm -f *.o *.out *.txt
