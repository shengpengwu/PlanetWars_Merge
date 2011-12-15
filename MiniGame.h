#ifndef MINIGAME_H
#define MINIGAME_H

class Lane;
#include <math.h>
#include <iostream>
#include "Model.h"
#include "Player.h"
#include "Unit.h"
#include "Lane.h"

class MiniGame
{
public:
	MiniGame(Node * node, Ship * attackerShip, Ship * defenderShip);
    
    Node * node;
    Ship * attacker;
    Ship * defender;

    Lane ** lanes;
    int selectedLane;
    
    void changeLane(int direction);
    void selectLane(int lane);
    void deployUnit(Ship * s, int type);
	void update();
    void drawGame();
};

#endif