//
// GamePhaseHandlers - Event handlers for different game phases
//

#ifndef BATTLESHIPS_GAMEPHASEHANDLERS_H
#define BATTLESHIPS_GAMEPHASEHANDLERS_H

#include "EventHandler.h"
#include "Board.h"
#include "GameManager.h"
#include "Mouse.h"
#include "Spritefactory.h"
#include "Renderables.h"
#include "Button.h"

// Handler for PLACING phase
class PlacingPhaseHandler : public EventHandler {
private:
    Board* m_board;
    GameManager* m_gameManager;
    Spritefactory* m_spriteFactory;
    Renderer* m_renderer;
    Button* m_shipButton;
    bool* m_hasSelection;
    bool* m_hasAdded;
    Piece* m_validPiece;
    Piece** m_currentPiece;
    Piece* m_noPiece;

public:
    PlacingPhaseHandler(Board* board, GameManager* gameManager,
                       Spritefactory* spriteFactory, Renderer* renderer,
                       Button* shipButton, bool* hasSelection, bool* hasAdded,
                       Piece* validPiece, Piece** currentPiece, Piece* noPiece);

    bool onMouseButtonPressed(const MouseButtonPressedEvent& event) override;
    bool onKeyPressed(const KeyPressedEvent& event) override;

private:
    void handleShipButtonClick(Vector2 mousePos);
    void handleShipPlacement(Vector2 mousePos);
};

// Handler for ATTACKING phase
class AttackingPhaseHandler : public EventHandler {
private:
    Board* m_board;
    GameManager* m_gameManager;

public:
    AttackingPhaseHandler(Board* board, GameManager* gameManager);

    bool onMouseButtonPressed(const MouseButtonPressedEvent& event) override;

private:
    void handleCellAttack(Vector2 mousePos);
};

#endif //BATTLESHIPS_GAMEPHASEHANDLERS_H
