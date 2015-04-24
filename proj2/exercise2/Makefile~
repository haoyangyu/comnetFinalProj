# Specify the compiler
CC = g++

CCOPTS = -g -Wall
LIBS = -lpthread

# Make the source
all:	sender receiver 

common_change.o : common_change.h common_change.cpp 
	$(CC) $(CCOPTS) -c common_change.cpp

receiver:  receiver.cpp common_change.o  
	$(CC) $(CCOPTS) common_change.o receiver.cpp -o receiver $(LIBS) 
 
sender:  sender.cpp common_change.o  
	$(CC) $(CCOPTS) common_change.o sender.cpp -o sender $(LIBS) 

clean :
	rm -f common_change.o sender receiver
