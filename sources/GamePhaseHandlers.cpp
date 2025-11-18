//
// GamePhaseHandlers Implementation
//

#include "GamePhaseHandlers.h"
#include "Vec2Utils.h"
#include <iostream>

// PlacingPhaseHandler Implementation
PlacingPhaseHandler::PlacingPhaseHandler(Board* board, GameManager* gameManager,
                                       Spritefactory* spriteFactory, Renderer* renderer,
                                       Button* shipButton, bool* hasSelection, bool* hasAdded,
                                       Piece* validPiece, Piece** currentPiece, Piece* noPiece)
    : m_board(board), m_gameManager(gameManager), m_spriteFactory(spriteFactory),
      m_renderer(renderer), m_shipButton(shipButton), m_hasSelection(hasSelection),
      m_hasAdded(hasAdded), m_validPiece(validPiece), m_currentPiece(currentPiece),
      m_noPiece(noPiece) {}

bool PlacingPhaseHandler::onMouseButtonPressed(const MouseButtonPressedEvent& event) {
    if (event.getButton() != MOUSE_BUTTON_LEFT) {
        return false;
    }

    Vector2 mousePos = event.getPosition();

    // Check if clicking on ship button
    if (CheckCollisionPointRec(mousePos, m_shipButton->rect())) {
        handleShipButtonClick(mousePos);
        return true;
    }

    // Check if placing a ship on the board
    if (!Mouse::getMouse()->getPiece()->isNull()) {
        if (CheckCollisionPointRec(mousePos, m_board->rect())) {
            handleShipPlacement(mousePos);
            return true;
        }
    }

    return false;
}

bool PlacingPhaseHandler::onKeyPressed(const KeyPressedEvent& event) {
    if (event.getKeyCode() == KEY_R) {
        Mouse::getMouse()->getPiece()->rotate(false);
        return true;
    }
    return false;
}

void PlacingPhaseHandler::handleShipButtonClick(Vector2 mousePos) {
    *m_hasSelection = !(*m_hasSelection);

    if (*m_hasSelection) {
        *m_currentPiece = m_validPiece;
        if (!(*m_hasAdded)) {
            m_renderer->addObj(*m_currentPiece);
            *m_hasAdded = true;
        }
        (*m_currentPiece)->setPos(mousePos);
        Mouse::getMouse()->setPiece(*m_currentPiece);
    } else {
        std::cout << "Removing piece " << (*m_currentPiece)->getId() << "\n";
        (*m_currentPiece)->removeFrom(m_renderer);
        *m_currentPiece = m_noPiece;
        Mouse::getMouse()->setPiece(*m_currentPiece);

        std::cout << Mouse::getMouse()->getPiece()->isNull();
        std::cout << (*m_currentPiece)->isNull();

        *m_hasAdded = false;
        std::cout << "removing frigate hover\n";
    }
}

void PlacingPhaseHandler::handleShipPlacement(Vector2 mousePos) {
    // Calculate cell position
    float boardMouseXOffset = mousePos.x - m_board->rect().x;
    float boardMouseYOffset = mousePos.y - m_board->rect().y;
    Rectangle cellRect = m_board->getCellAt(0, 0)->rect();
    float cellY = (int)(boardMouseYOffset / cellRect.height) * cellRect.height + m_board->rect().y;
    float cellX = (int)(boardMouseXOffset / cellRect.width) * cellRect.width + m_board->rect().x;

    Piece* mousePiece = Mouse::getMouse()->getPiece();

    // Clone the mousePiece onto the board
    Piece* toAdd = mousePiece;
    Piece* board_piece = m_spriteFactory->createFrigate(Vector2{cellX, cellY}, toAdd->getOffsets());

    m_gameManager->getCurrentPlayer()->addPiece(board_piece);

    bool added = m_board->addPiece(board_piece);
    if (!added) {
        std::cout << "cannot place here, there is already a ship!\n";
        for (auto piece : m_board->getAllPieces()) {
            std::cout << "already on board piece coords" << piece->coords().x << " "
                     << piece->coords().y << "\n";
        }
    } else {
        std::cout << "adding piece at X: " << (int)(boardMouseXOffset / cellRect.width)
                 << " Y: " << (int)(boardMouseYOffset / cellRect.height) << "\n";
    }
}

// AttackingPhaseHandler Implementation
AttackingPhaseHandler::AttackingPhaseHandler(Board* board, GameManager* gameManager)
    : m_board(board), m_gameManager(gameManager) {}

bool AttackingPhaseHandler::onMouseButtonPressed(const MouseButtonPressedEvent& event) {
    if (event.getButton() != MOUSE_BUTTON_LEFT) {
        return false;
    }

    Vector2 mousePos = event.getPosition();

    if (CheckCollisionPointRec(mousePos, m_board->rect())) {
        handleCellAttack(mousePos);
        return true;
    }

    return false;
}

void AttackingPhaseHandler::handleCellAttack(Vector2 mousePos) {
    Vector2 mouseCellVec = m_board->getBoardCell(mousePos);
    Cell* cell = m_board->getCellAt(mouseCellVec);

    // Check collision with every enemy piece
    Player* enemy = m_gameManager->getNextPlayer();
    auto pieceRoots = enemy->piecePositions;
    auto cells = std::vector<Cell*>{};

    for (auto p : pieceRoots) {
        Piece* piece = m_board->getPiece(p);
        for (int i = 0; i < piece->getOffsets().size(); i++) {
            cells.push_back(m_board->getCellAt(piece->getPartPos(i)));
        }
    }

    for (auto enemy_cell : cells) {
        auto op = std::equal_to<Vector2>();
        if (op(enemy_cell->coords(), mouseCellVec)) {
            enemy_cell->state = Cell::State::HIT_SUCCESS;
            std::cout << "you hit an enemy cell!\n";
            return;
        }
    }
}
