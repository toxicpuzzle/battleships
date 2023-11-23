//
// Created by toxic on 7/08/2023.
//

#ifndef VISUALISER_BOARD_H
#define VISUALISER_BOARD_H

#include <vector>
#include <string>
#include "raylib.h"
#include "Renderables.h"
#include <unordered_map>
#include <iostream>

class Cell;
class Board;
class Piece;

class Spritefactory;

class Cell : public Renderable{

public:
     enum State{
        HIT_SUCCESS,
        HIT_FAIL,
        HOVER,
        DEFAULT
    };

    constexpr static Vector2 globalDim{20.0,20.0};

    explicit Cell(Vector2 pos);

    void render() override;

    static std::unordered_map<State, Texture> stateTextures;

    State state{DEFAULT};
};

class Board : public Renderable {
    std::vector<std::vector<Cell*>> cells{};
    std::vector<Piece*> pieces;

public:
    Board(Vector2 pos, int rows, int cols, Spritefactory& s);

    Cell* getCellAt(int row, int col);

    Cell* getCellAt(Vector2 coords);

    bool addPiece(Piece* p);

    Piece* getPiece(Vector2 coord); // root position of piece

    auto& getAllPieces(){ return pieces; }

    Vector2 getBoardCell(Vector2 mousePos);

    // Renders cell backdrops then the pieces
    void render() override;
};

class Nullable{
    virtual bool isNull() = 0;
};

class Piece : public Renderable, public Nullable{

public:
    enum Direction{
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Piece(Vector2 pos, std::vector<std::pair<int,int>> offsets,
          std::vector<Texture> textures);

    void rotate(bool isCounter);

    void render() override;

    static bool collisionWith(Piece& a, Piece& b);

    void setPos(Vector2 newPos);

    Vector2 getPartPos(int idx);

    virtual bool isNull() override{ return false; }

    bool isAlive();

    auto getOffsets(){ return m_offsets; }

private:
    std::vector<std::pair<int,int>> m_offsets;
    std::vector<Texture> m_textures; // TODO how to make this static i.e. load once
    std::vector<bool> m_partAlive;
    int owner;
    //  could use factory approach.

};

class NoPiece: public Piece{
public:
    NoPiece() : Piece(Vector2 {0,0},
                      std::vector<std::pair<int,int>>{},
                      std::vector<Texture>{}) {};
    bool isNull() override{
        return true;
    }
};

#endif //VISUALISER_BOARD_H

