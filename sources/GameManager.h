//
// Created by toxic on 21/08/2023.
//

#ifndef VISUALISER_GAMEMANAGER_H
#define VISUALISER_GAMEMANAGER_H

#include "Player.h"

/**
 * Manages game rules e.g. ships allowed, quantity placed,
 * when playe wins, powerups e.t.c.
 */

enum GamePhase{
    PLACING,
    ATTACKING
};

class GameManager {

public:
    int currentPlayerIdx;
    std::vector<Player*> allPlayers; // TODO: Circular buffer so can get next player e.t.c.
    GamePhase phase;

    GameManager(std::vector<Player*> Player);

    GameManager(int num_players);

    void nextTurn();

    Player* getCurrentPlayer();

    Player* getNextPlayer();

};



#endif //VISUALISER_GAMEMANAGER_H
