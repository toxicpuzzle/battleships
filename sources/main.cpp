#include "raylib.h"
#include <cmath>
#include <vector>
#include <cstdlib>
#include "Renderables.h"
#include "Board.h"
#include "Button.h"
#include <iostream>
#include "Spritefactory.h"
#include "Mouse.h"
#include "GameManager.h"
#include "Vec2Utils.h"
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"



void initTextures() {
    // Initialise the cell textures;
    Cell::stateTextures[Cell::State::DEFAULT] = LoadTexture(ASSETS_PATH"cell.png");
    Cell::stateTextures[Cell::State::HOVER] = LoadTexture(ASSETS_PATH"cell_hover.png");
    Cell::stateTextures[Cell::State::HIT_SUCCESS] = LoadTexture(ASSETS_PATH"cell_invalid.png");
    Cell::stateTextures[Cell::State::HIT_FAIL] = LoadTexture(ASSETS_PATH"cell_valid.png");
}

void system_check_player_win() {

}

void system_cell_attack(Board* board, Player* enemy){
    Vector2 mousepos = GetMousePosition();
    Vector2 mouseCellVec = board->getBoardCell(mousepos);
    Cell* cell = board->getCellAt(mouseCellVec);
    bool leftClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
//    bool rightClicked = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

    if (leftClicked){
        // Check collision with every enemy piece
        auto pieceRoots = enemy->piecePositions;
        auto cells = std::vector<Cell*>{};
        for (auto p: pieceRoots){
            Piece* piece = board->getPiece(p);
            for (int i = 0; i < piece->getOffsets().size(); i++){
                cells.push_back(board->getCellAt(piece->getPartPos(i)));
            }
        }
        for (auto enemy_cell: cells){
            auto op = std::equal_to<Vector2>();
            if (op(enemy_cell->coords(), mouseCellVec)){
                enemy_cell->state = Cell::State::HIT_SUCCESS;
                std::cout << "you hit an enemy cell!\n";
                // TODO: Set the Piece's tracked cell at that offset for to dead state
                    // TODO: Unified interface to make it easier to fetch cells by coords.
                return;
            }
        }
    }


//    if (inside && leftClicked){
//        switch (cell->)
//        cell->state = Cell::State::HIT_FAIL;
//    }
//
//    if (inside){
//        if (this->state == DEFAULT){
//            this->state = HOVER;
//        } else if (leftClicked){
//            this->state = state != VALID ? VALID : DEFAULT;
//        } else if (rightClicked){
//            this->state = state != INVALID ? INVALID : DEFAULT;
//        }
//    } else {
//        if (this->state == HOVER) this->state = DEFAULT;
//    }
}

void set_player_piece_positions(Board *board, Player *curr_player, bool value) {
    for (auto pos: curr_player->piecePositions) {
        auto piece = board->getPiece(pos);
        piece->setRenderStatus(value);
    }
}

std::unordered_map<Cell::State, Texture> Cell::stateTextures{};

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    initTextures();

    SetTargetFPS(60);
    int time = 0;

    Renderer renderer{};
    Spritefactory s{};
    Board b{Vector2{30, 30}, 20, 20,s};
    renderer.addObj(&b);
    Button ship_button{Vector2{500, 200}, "frigate", LoadTexture(ASSETS_PATH"button.png")};
    Button turn_button{Vector2{500, 250}, "end turn", LoadTexture(ASSETS_PATH"button.png")};
    Button attack_phase_button{Vector2{500, 300}, "attack", LoadTexture(ASSETS_PATH"button.png")};
    std::vector<Player *> players{};

    // Game manager and player
    Player p1 = Player{0, b};
    Player p2 = Player{1, b};
    players.push_back(&p1);
    players.push_back(&p2);
    GameManager manager{players};

    renderer.addObj(&ship_button);
    renderer.addObj(&turn_button);
    renderer.addObj(&attack_phase_button);


//    Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works
    bool hasSelection{false};
    bool hasAdded{false};
    // If afactor yreturns hrom heap you can yus
    NoPiece noPiece = NoPiece();
    Piece *validPiece = s.createFrigate(Vector2{0, 0});
    Piece *piece = &noPiece;

    while (!WindowShouldClose()) {
        BeginDrawing();

        Vector2 mousePos = GetMousePosition();

        ClearBackground(RAYWHITE);

        std::string player_name = "Player" + std::to_string(manager.getCurrentPlayer()->id);

        DrawText(player_name.c_str(), 700, 200, 20, LIGHTGRAY);

        if (manager.phase == PLACING) {
            DrawText("Placing", 705, 230, 20, LIGHTGRAY);
            // Update code
            // Todo: implement react handler function i.e. pass in handler to button]
            // upon intialization about what you want it to do. i.e. button subscribes
            // to main game loop containing information
            if (CheckCollisionPointRec(mousePos, ship_button.rect())) {
                //
                bool leftClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
                if (leftClicked) {
                    hasSelection = !hasSelection;

                    if (hasSelection) {
                        piece = validPiece;
                        if (!hasAdded) {
                            renderer.addObj(piece);
                            hasAdded = true;
                        }
                        piece->setPos(mousePos);
                        Mouse::getMouse()->setPiece(piece);
                    } else {
                        std::cout << "Removing piece " << piece->getId() << "\n";
                        piece->removeFrom(&renderer);
                        piece = &noPiece;
                        Mouse::getMouse()->setPiece(piece);

                        std::cout << Mouse::getMouse()->getPiece()->isNull();
                        std::cout << piece->isNull();

                        hasAdded = false;
                        std::cout << "removing frigate hover\n";
                    }
                }
            }
            // Check if the R button is being presssed so we can rotate
            if (IsKeyPressed(KEY_R)) {
                Mouse::getMouse()->getPiece()->rotate(false);
            }

            // Find cell colliding with mouse in board
            // add piece to position starting from cell in board
            // Place the ship down
            if (!Mouse::getMouse()->getPiece()->isNull()) {
                // Check collission with board
                if (CheckCollisionPointRec(mousePos, b.rect()) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    // Assume cells have constant size through out game
                    float boardMouseXOffset = mousePos.x - b.rect().x;
                    float boardMouseYOffset = mousePos.y - b.rect().y;
                    Rectangle cellRect = b.getCellAt(0, 0)->rect();
                    float cellY = (int) (boardMouseYOffset / cellRect.height) * cellRect.height + b.rect().y;
                    float cellX = (int) (boardMouseXOffset / cellRect.width) * cellRect.width + b.rect().x;
                    Piece *mousePiece = Mouse::getMouse()->getPiece();

                    // Clone the mousePiece onto the board
                    Piece *toAdd = mousePiece;
                    Piece *board_piece = s.createFrigate(Vector2{cellX, cellY}, toAdd->getOffsets());
                    //! Need to create copy of piece to add to board, and not add the actual piece
                    manager.getCurrentPlayer()->addPiece(board_piece);

                    bool added = b.addPiece(board_piece);
                    if (!added) {
                        std::cout << "cannot place here, there is already a ship!\n";
                        for (auto piece: b.getAllPieces()) {
                            std::cout << "already on board piece coords" << piece->coords().x << " " <<
                                      piece->coords().y << "\n";
                        }
                    } else {
                        std::cout << "adding piece at X: " << (int) (boardMouseXOffset / cellRect.width)
                                  << " Y: " << (int) (boardMouseYOffset / cellRect.height) << "\n";
                    }
                }
            }

        } else if (manager.phase == ATTACKING) {
            // Attacking phase
            // clicking on cell - red if we hit, green if we do not
            DrawText("Attacking", 705, 230, 20, LIGHTGRAY);
            if (CheckCollisionPointRec(mousePos, b.rect())){
                system_cell_attack(&b, manager.getNextPlayer());
            }
        }

        // Button Logic - refactor to system and function pointers
        if (turn_button.isClicked(mousePos)) {
            set_player_piece_positions(&b, manager.getCurrentPlayer(), false);
            manager.nextTurn();
            std::cout << "adding new player piece positions";
            set_player_piece_positions(&b, manager.getCurrentPlayer(), true);
            manager.phase = PLACING;
        }
        if (attack_phase_button.isClicked(mousePos)){
            Mouse::getMouse()->setPiece(&noPiece);
            manager.phase = ATTACKING;
        }

        // Check end turn button
        piece->setPos(mousePos);

        // Render code;
        // TODO: Renderables have conditional rendering code based on current state of game
        // Hack: Remove all objects and only add back cells belonging to the owner for now
        renderer.render();

        EndDrawing();
        time++;
    }

    CloseWindow();

    return 0;
}
