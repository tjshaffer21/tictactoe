CC=g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

main: Board AI
	$(CC) main.cpp Board.o AI.o $(LIBS) -o tictactoe
	
Board:
	$(CC) -c Board.cpp $(LIBS)
    
AI:
	$(CC) -c AI.cpp

AITest: AI
	$(CC) ai_test.cpp ai.o -o test
    
clean:
	rm tictactoe.exe test.exe *.o