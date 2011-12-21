//
//  Lane.h
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#ifndef LANE_H
#define LANE_H

#include <vector>
#include "Model.h"
#include "DrawableGeometry.h"
#include "Ship.h"


using namespace std;

class Lane: public DrawableGeometry
{
public:
    Lane(Ship* atkShip, Ship* defShip);
    ~Lane();

    std::vector<Unit*> attackerUnits;
    std::vector<Unit*> defenderUnits;
    int furthestAttacker;
    int furthestDefender;
	Ship* attackShip;
	Ship* defendShip;
	int atkSummonTime;
	int defSummonTime;
    
    void setSelected(bool selected);
    void deployUnit(Unit * unit, bool attacker);
	void summonUnit();
    void advanceUnit(Unit * unit, bool attacker);
    void actUnit(Unit * unit, bool attacker);
    Unit* findFurthestUnit(bool attacker);
	Unit* findNextHeal(bool attacker);
    void tick();
	int getIndex(vector<Unit*> list, Unit* unit);
	//bool convertUnit(Unit *converter, Unit* convertee);
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    void compileDL();
    void draw();




};

#endif