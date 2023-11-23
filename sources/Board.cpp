//
// Created by toxic on 7/08/2023.
//

#include "Board.h"
#include <iostream>
#include <cmath>
#include "Mouse.h"
#include "Matrix.h"
#include "Spritefactory.h"

Cell::Cell(Vector2 pos) : Renderable(Rectangle{pos.x, pos.y, Cell::globalDim.x, Cell::globalDim.y}) {
}

void Cell::render() {
    DrawTexture(stateTextures[state], m_rect.x, m_rect.y, WHITE);
}

Board::Board(Vector2 pos, int rows, int cols, Spritefactory& s) :
        Renderable{Rectangle{pos.x, pos.y, cols * Cell::globalDim.x, rows * Cell::globalDim.y}} {
    float cell_x = pos.x;
    float cell_y = pos.y;
    for (int i = 0; i < rows; i++) {
        cells.push_back(std::vector<Cell*>{});
        cell_x = pos.x;
        for (int j = 0; j < cols; j++) {
            cells.back().push_back(s.createCell(Vector2{cell_x,cell_y}));
            cell_x += Cell::globalDim.x;
        }
        cell_y += Cell::globalDim.y;
    }
}

Vector2 Board::getBoardCell(Vector2 mousePos){
    float boardMouseXOffset = mousePos.x - this->rect().x;
    float boardMouseYOffset = mousePos.y - this->rect().y;
    Rectangle cellRect = this->getCellAt(0, 0)->rect();
    float cellY = (int) (boardMouseYOffset / cellRect.height) * cellRect.height + this->rect().y;
    float cellX = (int) (boardMouseXOffset / cellRect.width) * cellRect.width + this->rect().x;
    return Vector2{cellX, cellY};
}

Piece::Piece(Vector2 pos, std::vector<std::pair<int,int>> offsets,
             std::vector<Texture> textures) :
    Renderable(Rectangle{pos.x, pos.y, -1,-1}), m_offsets{offsets},
    m_textures{textures}, m_partAlive(textures.size(), true) {}

void Piece::render(){
    int textIdx = 0;
    for (int i = 0; i < m_offsets.size() ;i++){
        Vector2 part_pos = getPartPos(i);
        DrawTexture(m_textures[textIdx], part_pos.x, part_pos.y, WHITE);
    }
}

Vector2 Piece::getPartPos(int idx){
    if (idx > m_offsets.size())
        throw std::runtime_error("Invalid indeex for piece pos");
    return Vector2{m_rect.x + m_offsets[idx].first*Cell::globalDim.x,
                   m_rect.y + m_offsets[idx].second*Cell::globalDim.y};
}

void Piece::setPos(Vector2 newPos){
    m_rect.x = newPos.x;
    m_rect.y = newPos.y;
}

/*
 * Rotates the piece in the direction by 90 degrees around the centre
 * block with offset 0.
 */
void Piece::rotate(bool isCounter) {

    // Get rotation angle in radians
    double angle = 90.0;
    if (isCounter) angle = -90.0;
    angle = angle*3.141592/180;

    Matrix rotation = Matrix{};
    rotation.m0 = static_cast<float>(std::cos(angle));
    rotation.m4 = static_cast<float>(-std::sin(angle));
    rotation.m1 = static_cast<float>(std::sin(angle));
    rotation.m5 = static_cast<float>(std::cos(angle));


    for (std::pair<int, int> &pair: this->m_offsets) {
        Vector2 old_vec = Vector2{static_cast<float>(pair.first),
                                  static_cast<float>(pair.second)};
        Vector2 new_vec = mult(old_vec, rotation);
        std::cout << "New vec is" << new_vec.x << ", " <<  new_vec.y << "\n";
        pair.first = new_vec.x;
        pair.second = new_vec.y;
    }

    // print out the new rotatied blocks
    for (std::pair<int, int> &pair: this->m_offsets) {
        std::cout << "The pair is " << pair.first << ", " <<  pair.second << "\n";
    }
}
void Board::render(){
    // cell render
    for (std::vector<Cell*>& row: cells){
        for (auto cell: row){
            cell->render();
        }
    }

    // overlay stuff on each cell
    for(Piece* piece: pieces){
        if (piece->shouldRender()) piece->render();
    }
}

Cell* Board::getCellAt(int row, int col){
    return cells[row][col];
}

Cell* Board::getCellAt(Vector2 coords){
    // Convert coords to cell row/col
    Vector2 board_cell_coords = this->getBoardCell(coords);
    float boardMouseXOffset = board_cell_coords.x - this->rect().x;
    float boardMouseYOffset = board_cell_coords.y - this->rect().y;
    Rectangle cellRect = this->getCellAt(0, 0)->rect();
    int cellY = (int) (boardMouseYOffset / cellRect.height);
    int cellX = (int) (boardMouseXOffset / cellRect.width);
    return this->getCellAt(cellY, cellX);
}

bool Piece::collisionWith(Piece& a, Piece& b) {
    for (int i = 0; i < a.m_offsets.size(); i++){
        for (int j = 0; j < b.m_offsets.size(); j++){
            Vector2 aPos = a.getPartPos(i);
            Vector2 bPos = b.getPartPos(j);
            if (aPos.x == bPos.x && aPos.y == bPos.y) return true;
        }
    }
    return false;
}

bool Piece::isAlive() {
    for (bool cellStatus: m_partAlive){
        if (cellStatus) return true;
    }
    return false;
}



//Cell *Piece::getPart(Board* b, Vector2 vec) {
//    for (int i = 0; i < this->m_offsets.size(); i++){
//        if (vec == this->getPartPos(i);
//    }
//}

bool Board::addPiece(Piece* a){
    // Check collission with any existing pieces
    for (auto b: pieces){
        if (Piece::collisionWith(*a, *b)) return false;
    }
    pieces.push_back(a);

    return true;
}

Piece* Board::getPiece(Vector2 coord) {
    for (Piece* p: pieces){
        Vector2 pcoord = p->coords();
        if (pcoord.x == coord.x && pcoord.y == coord.y) return p;
    }
    return nullptr;
}
