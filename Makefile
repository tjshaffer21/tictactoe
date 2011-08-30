CC=g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

main: Board
	$(CC) main.cpp Board.o $(LIBS) -o tictactoe
	
Board:
	$(CC) -c Board.cpp $(LIBS)

clean:
	rm tictactoe.exe *.o