//
// Created by toxic on 8/08/2023.
//

#ifndef VISUALISER_SPRITEFACTORY_H
#define VISUALISER_SPRITEFACTORY_H

#include "Board.h"
#include <vector>
#include <memory>

class Spritefactory {

    Texture piece;
    // Todo store all under game objeccts with tags to allow for easy freeing,
    // Sprite factory should not need know details about other objects that's manager's responsibility
    std::vector<std::unique_ptr<Piece>> allPieces;
    std::vector<std::unique_ptr<Cell>> allCells;

public:

    Piece* createFrigate(Vector2 pos, std::vector<std::pair<int,int>> offsets = {
            {0,0},{0,1}
    });

    Cell* createCell(Vector2 pos);

    Spritefactory();
};



#endif //VISUALISER_SPRITEFACTORY_H
