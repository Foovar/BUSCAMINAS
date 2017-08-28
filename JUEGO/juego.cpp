//
//  juego.cpp
//  JUEGO
//
//  Created by Alex Paredes on 27/08/17.
//  Copyright © 2017 Alex Paredes. All rights reserved.
//

#include "juego.hpp"
#include <iostream>

Juego::Juego(){
    Juego::MAX_TABLE = 3;
    Juego::MAX_MINES = 2;
    Juego::MAX_PLAYERS = 2;
}

Juego::Juego(unsigned short level, unsigned short max_players){
    Juego::MAX_TABLE = (level == 1)*3+(level==2)*5+(level==3)*7+(level==4)*10;
    Juego::MAX_MINES = 2 * level;
    Juego::MAX_PLAYERS = max_players < 2 ? 2 : max_players > 5 ? 5 : max_players;
}

void Juego::start(){
    players = new short[MAX_PLAYERS];
    table = new short*[MAX_TABLE];
    current_turn = first_turn();
    
    createTable();
    createMines();
}

unsigned short Juego::first_turn() {
    return rand() % MAX_PLAYERS; // max points
}

unsigned short Juego::next_turn(){
    return current_turn+1 >= MAX_PLAYERS ? current_turn = 0 : current_turn++;
}

unsigned short Juego::randomNumber(){
    return rand() % 9 + 1; // max points
}

bool Juego::outOfRange(unsigned short x, unsigned short y){
    return (x - 1 < 0 || x - 1 >= MAX_TABLE) || ((y - 1 < 0 || y - 1 >= MAX_TABLE)) || (table[y -1][x -1] < 0);
}

void Juego::createTable(){
    for(int y = 0; y < MAX_TABLE; y++){
        table[y] = new short[MAX_TABLE];
        for(int x = 0; x<MAX_TABLE; x++){
            table[y][x] = randomNumber();
        }
    }
}

void Juego::createMines(){
    
    short x, y, i = 0;
    
    do{
        x = rand() % MAX_TABLE;
        y = rand() % MAX_TABLE;
        if(table[y][x] != 0){
            table[y][x] = 0;
            i++;
        }
    }while(i < MAX_MINES);
}

void Juego::showStats(){
    std::cout << " Total Jugadores: "<< MAX_PLAYERS << " Total de Minas: "<< MAX_MINES << " Slots restantes: "<< (MAX_TABLE * MAX_TABLE) - resolved <<" \n";
    std::cout << " Puntajes: \n";
    for (int i = 0; i < MAX_PLAYERS; i++) {
        std::cout << "\tJugador "<< i + 1 <<": "<< players[i] << " puntos. \n";
    }
    std::cout << std::endl;
}

unsigned short Juego::solvedSlots(){
    return resolved;
}

bool Juego::game_over(){
    return isGameOver;
}

void Juego::play(short x, short y){
    if(table[y - 1][x - 1] > 0){
        players[current_turn] += table[y - 1][x - 1];
        table[y - 1][x - 1] *= -1;
        if((MAX_TABLE * MAX_TABLE) - ++resolved == MAX_MINES ){
            won = true;
            isGameOver = true;
        }
        
        next_turn();
        
    } else isGameOver = true;
}

void Juego::showTable(bool solved){
    // Numeracion en X
    for (unsigned short a = 1; a <= MAX_TABLE; a++) { std::cout <<" ("<<a<<")  "; }
    std::cout << "X/Y";
    std::cout << std::endl;
    
    for (unsigned short i = 0; i < MAX_TABLE; i++) {
        // Dibujar cabeceras
        for (unsigned short a = 0; a < MAX_TABLE; a++) { std::cout <<".---. "; }
        std::cout << std::endl;
        
        // Dibujar contenedor
        for (unsigned short a = 0; a < MAX_TABLE; a++) {
            if(solved){
                if(table[i][a] == 0) std::cout<<"| X | ";
                else std::cout<<"| "<< abs(table[i][a]) <<" | ";
            }else{
                if( table[i][a] < 0 ) std::cout<<"| "<< abs(table[i][a]) <<" | ";
                else  std::cout<<"| * | ";
            }
        }
        //☠️
        // Numeracion en Y
        std::cout << "("<< i + 1 <<")";
        std::cout << std::endl;
        
        // Dibujar base
        for (unsigned short a = 0; a < MAX_TABLE; a++) { std::cout <<"`---´ "; }
        std::cout << std::endl;
    }
}

Juego::~Juego(){
    for(int i = 0; i< MAX_TABLE; i++){
        delete table[i];
    }
}

