# makefile sample

TARGET= testvec.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= vector.o testvec.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c
	
testvec.o: testvec.c vector.h
	$(CC) $(CFLAGS) -c testvec.c
	
clean:
	rm -f $(TARGET) $(OBJS)
