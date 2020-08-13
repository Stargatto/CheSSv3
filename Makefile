CC	= gcc
CFLAGS  = -O3

all: chess

chess: chessv3.o scacchiera.o
	$(CC) $(CFLAGS) chessv3.o scacchiera.o -o chess

chessv3.o: chessv3.c
	$(CC) $(CFLAGS) -c chessv3.c

scacchiera.o: scacchiera.c
	$(CC) $(CFLAGS) -c scacchiera.c

test: test.o scacchiera.o
	$(CC) $(CFLAGS) test.o scacchiera.o -o test	

clean:
	rm -rf *o chess test *~
					
