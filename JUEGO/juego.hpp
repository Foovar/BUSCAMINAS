//
//  juego.hpp
//  JUEGO
//
//  Created by Alex Paredes on 27/08/17.
//  Copyright © 2017 Alex Paredes. All rights reserved.
//

#ifndef juego_hpp
#define juego_hpp

#include <stdio.h>

class Juego {
    private:
    //short **table;
    short **table;
    short * players;
    unsigned short MAX_MINES;
    unsigned short MAX_TABLE;
    unsigned short MAX_PLAYERS;
    bool isGameOver = false;
    unsigned short resolved = 0;
    bool won = false;
    unsigned short current_turn;
    
    public:
    Juego();
    Juego(unsigned short, unsigned short);
    ~Juego();
    
    unsigned short randomNumber();
    bool outOfRange(unsigned short x, unsigned short y);
    unsigned short first_turn();
    unsigned short next_turn();
    unsigned short getTurn() { return current_turn; };
    unsigned short solvedSlots();
    bool wasWinner(){ return won; }
    bool game_over();
    void createTable();
    void createMines();
    void showTable(bool);
    void showStats();
    void play(short, short);
    void start();
};


#endif /* juego_hpp */
