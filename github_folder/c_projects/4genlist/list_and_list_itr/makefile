# makefile for list and list_itr

TARGET_LIST = testlist.out
TARGET_ITR = test_list_itr.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS_LIST = testlist.o list.o
OBJS_ITR = test_list_itr.o list_itr.o list.o

$(TARGET_LIST): $(OBJS_LIST) $(TARGET_ITR)
	$(CC) -o $(TARGET_LIST) $(OBJS_LIST)

$(TARGET_ITR): $(OBJS_ITR)
	$(CC) -o $(TARGET_ITR) $(OBJS_ITR)

list.o: list.c listinternal.h
	$(CC) $(CFLAGS) -c list.c

testlist.o: testlist.c listinternal.h
	$(CC) $(CFLAGS) -c testlist.c

list_itr.o: list_itr.c listinternal.h 
	$(CC) $(CFLAGS) -c list_itr.c

test_list_itr.o: test_list_itr.c listinternal.h
	$(CC) $(CFLAGS) -c test_list_itr.c
	
clean:
	rm -f $(TARGET_LIST) $(TARGET_ITR) $(OBJS_LIST) $(OBJS_ITR)

val_grind_itr:
	valgrind --log-file=val_grind_itr.log --leak-check=full --track-origins=yes ./$(TARGET_ITR)

val_grind_list:
	valgrind --log-file=val_grind_list.log --leak-check=full --track-origins=yes ./$(TARGET_LIST)
