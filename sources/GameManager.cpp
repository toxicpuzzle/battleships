//
// Created by toxic on 21/08/2023.
//

#include "GameManager.h"
/**
 * Initializes game manager
 * @param players list of players, player goes in order 0, 1, 2...
 */
GameManager::GameManager(std::vector<Player*> players){
    this->allPlayers = players;
    this->phase = PLACING;
    this->currentPlayerIdx = 0;
}

void GameManager::nextTurn() {
    this->currentPlayerIdx = (this->currentPlayerIdx+1)%this->allPlayers.size();
}

Player* GameManager::getCurrentPlayer() {
    return this->allPlayers[this->currentPlayerIdx];
}

Player *GameManager::getNextPlayer() {
    return this->allPlayers[(this->currentPlayerIdx+1)%this->allPlayers.size()];
}
