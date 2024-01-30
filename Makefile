#set noexpandtab

CC = gcc
CFLAGS = -O2 -lSDL2 -lSDL2main -I./include/
OBJS = main.o glad.o initalize_free.o

all: gpuFractal

gpuFractal: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o gpuFractal

$(OBJS): src/*.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o gpuFractal












