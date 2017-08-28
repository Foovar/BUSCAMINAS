//
//  main.cpp
//  JUEGO
//
//  Created by Alex Paredes on 26/08/17.
//  Copyright © 2017 Alex Paredes. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "juego.hpp"

int main(int argc, const char * argv[]){
    srand((int)time(NULL));
    // menu inicial
    short level, max_players, x, y;
    
    std::cout << "\t+++ BUSCAMINAS MAINFRAME +++\n"
    << "Facil(1)\t Normal(2)\t Dificil(3)\t Experto(4)\n"
    << "Elige un nivel: ";
    std::cin >> level;
    std::cout << "Cantidad de jugadores(entre 2 y 5): ";
    std::cin >> max_players;
    
    Juego buscaminas(level, max_players);
    buscaminas.start();
    
    do{
        system("clear");
        std::cout << "  +++ BUSCAMINAS MAINFRAME +++\n";
        buscaminas.showStats();
        buscaminas.showTable(false);
    coor:
        std::cout << "Turno del jugador Nº "<< buscaminas.getTurn() + 1 << std::endl;
        std::cout << "\tIngresa CoorX: ";
        std::cin >> x;
        std::cout << "\tIngresa CoorY: ";
        std::cin >> y;
        
        if(!std::cin || buscaminas.outOfRange(x, y)){
            std::cout << "\n¡Ingresa las coordenadas correctas!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto coor;
        }
        
        buscaminas.play(x, y);
        
    }while(!buscaminas.game_over());
    
    system("clear");
    std::cout << "¡¡¡¡ SE TERMINO EL JUEGO. !!!!" << std::endl;
    buscaminas.showStats();
    buscaminas.showTable(true);
    std::cout << (!buscaminas.wasWinner() ? "¡PERDISTE! " : "¡GANASTE!") <<" Jugador: " << buscaminas.getTurn() + 1 << std::endl;

    
}
