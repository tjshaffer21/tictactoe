#include "ai.h"
#include <iostream>
AI::AI(char piece, char oppiece) {
	this->piece   = piece;
    this->oppiece = oppiece;
    
    srand(time(NULL));
}

inline bool AI::isFull(char* brd) {
	size_t i;
	for(i = 0; i < BOARD_SIZE; i++) {
		if(brd[i] == -1) { return false; }
	}
	
	return true;
}

char AI::getPiece()       { return piece; }
void AI::run(char *board) {
    char *temp;
    size_t i;
    list<char *> *pos = minimax(board);

    temp = pos->front();
    pos->pop_front();
    for(size_t i = 0; i < BOARD_SIZE; i++) {
        board[i] = temp[i];
    }
    delete temp;

    if(pos->size() >= 0) {
        while(!pos->empty()) {
            temp = pos->front();
            pos->pop_front();
            
            delete temp;

        }
    }

    delete pos;
}
    
list<char *> * AI::minimax(char *node) {
    size_t i;
    size_t k;
    int value;
    char *temp;
    
    int alpha = -1;// numeric_limits<int>::min();
    list<char *> *pos = new list<char *>();
    for(i = 0; i < BOARD_SIZE; i++) {
        if(node[i] == B) {
            node[i] = piece;
            
            value = minimaxSearch(node, oppiece);
            if(value > alpha) {
                temp = new char[BOARD_SIZE];
                for(k = 0; k < BOARD_SIZE; k++) {
                    temp[k] = node[k];
                }
                pos->push_front(temp);
                alpha = value;
            }
            
            node[i] = B;
        }
    }
    
    return pos;
}

int AI::minimaxSearch(char *node, char p) {
    size_t i;
    int wl = winlosedraw(node);
	if(wl == 1)  { return 1;  } 
    if(wl == -1) { return -1; }
    if(wl == 0)  { return 0;  }

    int alpha;
    
    (p == piece) ? (alpha = numeric_limits<int>::min()) : 
        (alpha = numeric_limits<int>::max());
    for(i = 0; i < BOARD_SIZE; i++) {
        if(node[i] == B) {
            node[i] = p;
            
            (p == piece) ? (alpha = max(alpha, minimaxSearch(node, oppiece))) :
                (alpha = min(alpha, minimaxSearch(node, piece)));
            
            node[i] = B;
        }
    }
    return alpha;
}

char AI::winlosedraw(char *board) {
    size_t i;
    bool empty = false;
	for(i = 0; i < BOARD_SIZE; i++) {
		if(board[i] == B) {
			empty = true;
		}
	}
    
    if(empty == false) { return 0; }
    
	char h1 = board[0] + board[1] + board[2];
	char h2 = board[3] + board[4] + board[5];
	char h3 = board[6] + board[7] + board[8];
	
	char v1 = board[0] + board[3] + board[6];
	char v2 = board[1] + board[4] + board[7];
	char v3 = board[2] + board[5] + board[8];
	
	char d1 = board[0] + board[4] + board[8];
	char d2 = board[2] + board[4] + board[6];

    int winvalue  = piece * 3;
    int losevalue = oppiece * 3;
	if(h1 == winvalue || h2 == winvalue || h3 == winvalue || v1 == winvalue
      || v2 == winvalue || v3 == winvalue || d1 == winvalue || d2 == winvalue) {
        return 1;
	} else if (h1 == losevalue || h2 == losevalue || h3 == losevalue || 
      v1 == losevalue || v2 == losevalue || v3 == losevalue || d1 == losevalue
      || d2 == losevalue) {
        return -1;
	}

	return -2;
}
