//
// Created by toxic on 21/08/2023.
//

#ifndef VISUALISER_PLAYER_H
#define VISUALISER_PLAYER_H
#include <vector>
#include <unordered_map>
#include "Board.h"
#include "Vec2Utils.h"



//auto equal = [](const Vector2& l, const Vector2& r){return l.x == r.x && l.y == r.y;};

/**
 * Stores information about each player
 * e.g. ships placed, pieces they own on the board, powerups
 * e.t.c.
 */
class Player {

public:
    Board& board;
    std::vector<Vector2> piecePositions{};
    std::unordered_map<Vector2, bool> pieceAlive;
    int id;

    Player(int id, Board& board);

    bool hasLost();

    bool addPiece(Piece* toAdd);
};


#endif //VISUALISER_PLAYER_H
