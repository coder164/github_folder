# makefile sample

TARGET= testheap.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= heap.o testheap.o vector.o
PATHS= ../2genvector/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
heap.o: heap.c heap.h $(PATHS)vector.h
	$(CC) $(CFLAGS) -I $(PATHS) -c heap.c 

testheap.o: testheap.c heap.h $(PATHS)vector.h
	$(CC) $(CFLAGS) -I $(PATHS) -c testheap.c

vector.o: $(PATHS)vector.c $(PATHS)vector.h
	$(CC) $(CFLAGS) -I $(PATHS) -c $(PATHS)vector.c
	
clean:
	rm -f $(TARGET) $(OBJS)
