//
// Created by toxic on 8/08/2023.
//

#include "Spritefactory.h"
#include "raylib.h"

Spritefactory::Spritefactory() {
    piece = LoadTexture(ASSETS_PATH"piece.png");
}

Piece* Spritefactory::createFrigate(Vector2 pos, std::vector<std::pair<int,int>> offsets){
    // Default is in vertical position
    std::vector<Texture> textures = {piece, piece};
    auto p = std::make_unique<Piece>(Piece{pos, std::move(offsets), textures});
    auto raw_p = p.get(); // Move nulls original p (l-value) by turning it into r-value, so we need to fetch raw pointer here
    this->allPieces.push_back(std::move(p)); // convert unique ptr to r value to release ownership of it
    return raw_p;
}

Cell* Spritefactory::createCell(Vector2 pos){
    auto cell = std::make_unique<Cell>(Cell{pos});
    auto raw_cell = cell.get();
    this->allCells.push_back(std::move(cell));
    return raw_cell;
}

