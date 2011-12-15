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

	int counter;

	Ship * attackShip;
	Ship * defendShip;
    
    void changeLane(int direction);
    void selectLane(int lane);
    void deployUnit(Ship * s, int type);
	void update();
    void drawGame();
	void generateUnits();
};

#endif