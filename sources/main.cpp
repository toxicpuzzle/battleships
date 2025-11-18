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
#include "EventManager.h"
#include "GamePhaseHandlers.h"
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

    // Event system setup
    EventManager eventManager;

    // Game state
    bool hasSelection{false};
    bool hasAdded{false};
    NoPiece noPiece = NoPiece();
    Piece *validPiece = s.createFrigate(Vector2{0, 0});
    Piece *piece = &noPiece;

    // Create phase handlers
    PlacingPhaseHandler placingHandler(&b, &manager, &s, &renderer, &ship_button,
                                      &hasSelection, &hasAdded, validPiece, &piece, &noPiece);
    AttackingPhaseHandler attackingHandler(&b, &manager);

    // Setup button callbacks
    turn_button.setOnClick([&]() {
        set_player_piece_positions(&b, manager.getCurrentPlayer(), false);
        manager.nextTurn();
        std::cout << "adding new player piece positions";
        set_player_piece_positions(&b, manager.getCurrentPlayer(), true);
        manager.phase = PLACING;

        // Update event handlers for new phase
        eventManager.clearHandlers();
        eventManager.addHandler(&placingHandler);
        eventManager.addHandler(&turn_button);
        eventManager.addHandler(&attack_phase_button);
    });

    attack_phase_button.setOnClick([&]() {
        Mouse::getMouse()->setPiece(&noPiece);
        manager.phase = ATTACKING;

        // Update event handlers for new phase
        eventManager.clearHandlers();
        eventManager.addHandler(&attackingHandler);
        eventManager.addHandler(&turn_button);
        eventManager.addHandler(&attack_phase_button);
    });

    // Register initial handlers (PLACING phase)
    eventManager.addHandler(&placingHandler);
    eventManager.addHandler(&turn_button);
    eventManager.addHandler(&attack_phase_button);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Poll and dispatch all events through the event system
        eventManager.pollEvents();

        // Update game state
        Vector2 mousePos = GetMousePosition();
        piece->setPos(mousePos);

        // Render UI
        std::string player_name = "Player" + std::to_string(manager.getCurrentPlayer()->id);
        DrawText(player_name.c_str(), 700, 200, 20, LIGHTGRAY);

        if (manager.phase == PLACING) {
            DrawText("Placing", 705, 230, 20, LIGHTGRAY);
        } else if (manager.phase == ATTACKING) {
            DrawText("Attacking", 705, 230, 20, LIGHTGRAY);
        }

        // Render all game objects
        renderer.render();

        EndDrawing();
        time++;
    }

    CloseWindow();

    return 0;
}
