# makefile for list_functions

TARGET = testfunc.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = list.o list_itr.o listfunc.o testfunc.o
P_LIST = ../list_and_list_itr/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

list.o: $(P_LIST)list.c $(P_LIST)listinternal.h
	$(CC) $(CFLAGS) -I $(P_LIST) -c $(P_LIST)list.c

list_itr.o: $(P_LIST)list_itr.c $(P_LIST)listinternal.h
	$(CC) $(CFLAGS) -I $(P_LIST) -c $(P_LIST)list_itr.c

listfunc.o: listfunc.c list_functions.h $(P_LIST)listinternal.h
	$(CC) $(CFLAGS) -I $(P_LIST) -c listfunc.c

testfunc.o: testfunc.c list_functions.h $(P_LIST)listinternal.h
	$(CC) $(CFLAGS) -I $(P_LIST) -c testfunc.c
	
clean:
	rm -f $(TARGET) $(OBJS)
