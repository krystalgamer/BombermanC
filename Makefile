CC= gcc
LIBS = -lallegro -lallegro_image -lallegro_dialog
OBJ = main.o player.o map.o bomb.o
CFLAGS = -Wall -std=c99
all: bomb

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

bomb: $(OBJ)
	gcc -o bomb $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf *.o
