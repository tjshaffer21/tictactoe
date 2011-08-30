#ifndef __BOARD_H__
#define __BOARD_H__

#include <SFML/graphics.hpp>
#include "ai.h"

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_SIZE 9
class Board {
    private:
        enum pieces_t { X = 2, O = 3, B = -1 } Pieces;
      
        sf::RenderWindow *window;
          
        // width, height, width/3, height/3, (width/3)*2, (height/3)*2
        unsigned int regions[6];
        char board[9];
        // -1 Still Playing, 0 Draw, 2 X, 3 O
        char match;
        size_t score[3];        // X, O, C
        char player;            // X = 2, O = 3
        AI *ai;
          
        /**********************************************************************
         * Increment the score of the winner (or draw).                       *
         * @note variable score is modified.                                  *
         *********************************************************************/
        inline void gameMatch();
          
        /**********************************************************************
         * Reset game values.                                                 *
         * @note variables player, match, board are reset.                    *
         *********************************************************************/
        inline void gameReset();
          
        /**********************************************************************
         * Check if win/draw condition has been met.                          *
         * @return int - 0 if still playing, 1 if conditon met.               *
         * @note variable match is modified.                                  *
         *********************************************************************/
        int checkWinCondition();
          
        /**********************************************************************
         * Switches active player.                                            *
         * @note variable player is modified.                                 *
         *********************************************************************/
        void switchPlayer();
         
        /**********************************************************************
         * Returns the box where piece will be drawn.                         *
         * @param int  - Regions to obtain bounding box.                      *
         * @return int * - Top Left x,y; Top Right x,y; Bottom Left x,y       *
         *       Bottom Right x,y                                             *
         *********************************************************************/
        unsigned int * getBoundingBox(int);
          
        /**********************************************************************
         * Draw text at specified region.                                     *
         * @param const char*                                                 *
         * @param int - X                                                     *
         * @param int - Y                                                     *
         *********************************************************************/
        void drawText(const char*, int, int);
      
    public:
        /**********************************************************************
         * Constructor                                                        *
         * @param sf::RenderWindow * - Takes the rendering window for         *
         *          drawing purposes.                                         *
         *********************************************************************/
        Board(sf::RenderWindow *);
      
        /**********************************************************************
         * Convert screen coordinates to board coordinates.                   *
         * @param  int - X screen coordinate.                                 *
         * @return int - X board coordinate.                                  *
         *********************************************************************/
        inline int getXRegion(int);
      
        /**********************************************************************
         * Convert screen coordinates to board coordinates.                   *
         * @param int - Y screen coordinate.                                  *
         * @return int - Y board coordinate.                                  *
         *********************************************************************/
        inline int getYRegion(int);
      
        /**********************************************************************
         * Check for events used by the board.                                *
         * @param sf::Event *                                                 *
         *********************************************************************/
        void checkEvents(sf::Event *);
      
        /**********************************************************************
         * Draw to the screen.                                                *
         *********************************************************************/
        void draw(); 
};

#endif
