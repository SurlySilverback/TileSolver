CC = g++
CFLAGS = -Wall -Werror -W -Wextra -g --std=c++11

all: main.o GraphSearch.o Node.o Grid.o Node.o
	$(CC) $(CFLAGS) *.o -o graphSearch

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Grid.o: Grid.cpp
	$(CC) $(CFLAGS) -c Grid.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

GraphSearch.o: GraphSearch.cpp
	$(CC) $(CFLAGS) -c GraphSearch.cpp

clean:
	rm -f *.o

