#include "Board.h"
#include <stdio.h>
Board::Board(sf::RenderWindow *win) {
    int i;
    window = win;

    regions[0] = window->GetWidth();
    regions[1] = window->GetHeight();
    regions[2] = regions[0]/3;
    regions[3] = regions[1]/3;
    regions[4] = regions[2] << 1;
    regions[5] = regions[3] << 1; 

    player   = X;
    ai       = new AI(O,X);
    
    match    = -1;
    
    score[0] = 0;
    score[1] = 0;
    score[2] = 0;
 
    for(i = 0; i < BOARD_SIZE; i++) {
        board[i] = B;
    }
}

Board::~Board() {}

int Board::checkWinCondition() {
     int i;
     bool empty = false;
     for(i = 0; i < BOARD_SIZE; i++) {
        if(board[i] == B) {
            empty = true;
            break;
        }
     }
     
     if(empty == false) { match = 0; }
     
     // x := 2, o := 3
     // el1 + el2 + el3 = 6 then X wins
     // el1 + el2 + el3 = 9 then O wins
     char h1 = board[0] + board[1] + board[2];
     char h2 = board[3] + board[4] + board[5];
     char h3 = board[6] + board[7] + board[8];
     
     char v1 = board[0] + board[3] + board[6];
     char v2 = board[1] + board[4] + board[7];
     char v3 = board[2] + board[5] + board[8];
     
     char d1 = board[0] + board[4] + board[8];
     char d2 = board[2] + board[4] + board[6];

     if(h1 == 6 || h2 == 6 || h3 == 6 || v1 == 6 || v2 == 6 || v3 == 6 ||
        d1 == 6 || d2 == 6) {
           match = 2;
     } else if (h1 == 9 || h2 == 9 || h3 == 9 || v1 == 9 || v2 == 9 || 
        v3 == 9 || d1 == 9 || d2 == 9) {
          match = 1;
     }
 
    switch(match) {
        case 0:
        case 1:
        case 2:
            return 1;
        default:
            return 0;
    }
}

void Board::switchPlayer() { 
    (player == O) ? (player = X) : (player = O); 
    
    // Run AI.
    if(player == ai->getPiece()) {
        ai->run(board);
        if(checkWinCondition() == 0) {
            switchPlayer();
        } else {
            gameMatch();
        }
    }
    
}

unsigned int * Board::getBoundingBox(int xy) {
    // 0,1 - Top Left; 2,3 - Top Right; 4,5 - Bottom Left; 6,7 - Bottom Right
    unsigned int *box = new unsigned int[8];
    switch(xy) {
        case 0:
            box[0] = 0;
            box[1] = 0;
            box[2] = regions[2];
            box[3] = 0;
            box[4] = 0;
            box[5] = regions[3];
            box[6] = regions[2];
            box[7] = regions[3];
            break;
        case 1:
            box[0] = regions[2];
            box[1] = 0;
            box[2] = regions[4];
            box[3] = 0;
            box[4] = regions[2];
            box[5] = regions[3];
            box[6] = regions[4];
            box[7] = regions[3];
            break;
        case 2: 
            box[0] = regions[4];
            box[1] = 0;
            box[2] = regions[0];
            box[3] = 0;
            box[4] = regions[4];
            box[5] = regions[3];
            box[6] = regions[0];
            box[7] = regions[3];
            break;
        case 3:
            box[0] = 0;
            box[1] = regions[3];
            box[2] = regions[2];
            box[3] = regions[3];
            box[4] = 0;
            box[5] = regions[5];
            box[6] = regions[2];
            box[7] = regions[5];
            break;
        case 4:
            box[0] = regions[2];
            box[1] = regions[3];
            box[2] = regions[4];
            box[3] = regions[3];
            box[4] = regions[2];
            box[5] = regions[5];
            box[6] = regions[4];
            box[7] = regions[5];
            break;
        case 5:
            box[0] = regions[4];
            box[1] = regions[3];
            box[2] = regions[0];
            box[3] = regions[3];
            box[4] = regions[4];
            box[5] = regions[5];
            box[6] = regions[0];
            box[7] = regions[5];
            break;
        case 6:
            box[0] = 0;
            box[1] = regions[5];
            box[2] = regions[2];
            box[3] = regions[5];
            box[4] = 0;
            box[5] = regions[1];
            box[6] = regions[2];
            box[7] = regions[1];
            break;
        case 7:
            box[0] = regions[2];
            box[1] = regions[5];
            box[2] = regions[4];
            box[3] = regions[5];
            box[4] = regions[2];
            box[5] = regions[1];
            box[6] = regions[4];
            box[7] = regions[1];
            break;
        case 8:
            box[0] = regions[4];
            box[1] = regions[5];
            box[2] = regions[0];
            box[3] = regions[5];
            box[4] = regions[4];
            box[5] = regions[1];
            box[6] = regions[0];
            box[7] = regions[1];
            break;
    }

    return box;
}

inline int Board::getXRegion(int x) {
    if(x > 0 && x < regions[2]) { return 0; }
    if(x >= regions[2] && x < regions[4]) { return 1; }
    if(x >= regions[4] && x < regions[0]) { return 2; }
}

inline int Board::getYRegion(int y) {
    if(y > 0 && y < regions[3]) { return 0; }
    if(y >= regions[3] && y < regions[5]) { return 1; }
    if(y >= regions[5] && y < regions[1]) { return 2; }
}

inline void Board::gameReset() {
    int i;
    for(i = 0; i < BOARD_SIZE; i++) {
        board[i] = B;
    }

    player = X;
    match  = -1;
    window->Clear();
}

inline void Board::gameMatch() {
    switch(match) {
        case 0:
            score[2] = score[2] + 1;
            break;
        case 1:
            score[1] = score[1] + 1;
            break;
        case 2:
            score[0] = score[0] + 1;
            break;
    }
}

void Board::checkEvents(sf::Event *event) { 
    if(match != -1) {
        if(event->Type == sf::Event::KeyPressed) {
            if(event->Key.Code == sf::Key::Y) {
                gameReset();
            } else if(event->Key.Code == sf::Key::N) {
                window->Close();
            }
        }
    } else {

        if((event->Type == sf::Event::MouseButtonPressed) &&
            (event->MouseButton.Button == sf::Mouse::Left)) {
              short xy = getXRegion(event->MouseButton.X) + BOARD_HEIGHT * 
                 getYRegion(event->MouseButton.Y);
               
            if(board[xy] == B) {
                board[xy] = player;
                if(checkWinCondition() == 0) {
                    switchPlayer();
                } else {
                    gameMatch();
                }
            }
        }
    }
}

inline void Board::drawText(const char* str, int x, int y) {
    sf::String Text;
    Text.SetText(str);
    Text.SetSize(50);
    Text.SetFont(sf::Font::GetDefaultFont());
    Text.SetColor(sf::Color::Red);
    Text.SetX(x);
    Text.SetY(y);

    window->Draw(Text);
}

void Board::draw() { 
    window->Clear();

    sf::Shape bLine, fLine, Circle;

    sf::Shape vLine1 = sf::Shape::Line(regions[2], 0, regions[2], regions[1], 
            5.f, sf::Color::White);
    sf::Shape vLine2 = sf::Shape::Line(regions[4], 0, regions[4], regions[1],
            5.f, sf::Color::White);
    sf::Shape hLine1 = sf::Shape::Line(0, regions[3], regions[0], regions[3],
            5.f, sf::Color::White);
    sf::Shape hLine2 = sf::Shape::Line(0, regions[5], regions[0], regions[5],
            5.f, sf::Color::White);
            
    int i = 0;
    for(i = 0; i < BOARD_SIZE; i++) {
        unsigned int *bounding_box = getBoundingBox(i);

        switch(board[i]) {
            case 2:
                bLine = sf::Shape::Line(bounding_box[0], 
                      bounding_box[1], bounding_box[6], 
                      bounding_box[7], 5.f, sf::Color::White);
                fLine = sf::Shape::Line(bounding_box[4], 
                      bounding_box[5], bounding_box[2], 
                      bounding_box[3], 5.f, sf::Color::White);
                      
                window->Draw(bLine);
                window->Draw(fLine);
                break;
            case 3:
                float x = (float)bounding_box[6] - (regions[2] / 2); 
                float y = (float)bounding_box[7] - (regions[3] / 2);
                Circle = sf::Shape::Circle(x, y, 100.f, sf::Color::White);
                       
                window->Draw(Circle);
                break;
        }   

        delete bounding_box;
        }

    window->Draw(vLine1);
    window->Draw(vLine2);
    window->Draw(hLine1);
    window->Draw(hLine2);

    if(match != -1) {
        if(match == 2) {
            drawText("Winner X!", regions[2], regions[3]);
        } else if(match == 1) {
            drawText("Winner O!", regions[2], regions[3]);
        } else if(match == 0) {
            drawText("Cat's Game!", regions[2], regions[3]);
        }

        drawText("Play Again (Y/N)", regions[2], regions[3]+50);

        char scr[255];
        sprintf(scr, "Score: X %d, O: %d, C: %d", score[0], score[1], score[2]);
        drawText(scr, regions[2], regions[3]+100);
    }
}
