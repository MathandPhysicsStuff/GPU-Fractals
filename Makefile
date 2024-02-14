#set noexpandtab

CC = gcc
CFLAGS = -O2 -lm -lSDL2 -lSDL2main -I./include/
SRCS = *.c
OBJS = *.o

all: gpuFractal

gpuFractal: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o gpuFractal

$(OBJS): src/*.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o gpuFractal












