//
// Created by toxic on 10/08/2023.
//

#ifndef VISUALISER_MOUSE_H
#define VISUALISER_MOUSE_H

#include "Board.h"

class Mouse {
    Piece* carried;
    static Mouse* globalMouse;

    Mouse();

public:
    Piece* getPiece();
    void setPiece(Piece* p);
    static Mouse* getMouse();
};


#endif //VISUALISER_MOUSE_H
