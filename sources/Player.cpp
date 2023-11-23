//
// Created by toxic on 21/08/2023.
//

#include "Player.h"

Player::Player(int id, Board &board) : board{board}, id{id}, pieceAlive{} {
}

bool Player::addPiece(Piece* toAdd) {
    this->piecePositions.push_back(toAdd->coords());
    this->pieceAlive[toAdd->coords()] = true;
    return true;
}
