#ifndef __AI_H__
#define __AI_H__
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <limits>
#include <list>

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_SIZE 9
using namespace std;
class AI {
	private:
        enum pieces_t { X = 2, O = 3, B = -1 } Pieces;
        char oppiece;
        char piece;
  
        /**********************************************************************
         *  Minimax algorithm.                                                *
         *  @param char *                                                     *
         *  @return list<char *> *                                            *
         *********************************************************************/
        list<char *> * minimax(char *);

        /**********************************************************************
         * Minimax algorithm.                                                 *
         * @param char *                                                      *
         * @param char                                                        *
         * @return int                                                        *
         *                                                                    *
         *  Algorithm:                                                        *
         *      alpha := -1                                                   *
         *      foreach child in node                                         *
         *          alpha := max(alpha, (-)minimaxSearch(node)                *
         *      end                                                           *
         *      return alpha                                                  *
         *********************************************************************/         
        int minimaxSearch(char *, char);
        
        /**********************************************************************
         * Check if the given board is full.                                  *
         * @param char *                                                      *
         * @return bool                                                       *
         *********************************************************************/
        inline bool isFull(char *);
  
        /**********************************************************************
         *  Determine if the board meets a win/lose/draw condition.           *
         *  @param char *                                                     *
         *  @return char    - 0 Draw, 1 Win, -1 Lose.                         *
         *********************************************************************/
        char winlosedraw(char *);

  
    public:
        AI(char, char);
        void run(char *);
        char getPiece();
};

#endif
