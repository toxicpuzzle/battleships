//
// Created by toxic on 10/08/2023.
//

#include <iostream>
#include "Mouse.h"
#include "Board.h"

Mouse::Mouse() : carried{new NoPiece()}{}

Mouse* Mouse::getMouse(){
    if (globalMouse == nullptr){
        std::cout << "created new mouse\n";
        globalMouse = new Mouse();
    }
    return globalMouse;
}

void Mouse::setPiece(Piece* p){
    this->carried = p;
}

Piece* Mouse::getPiece(){
    return carried;
}

Mouse* Mouse::globalMouse = nullptr;