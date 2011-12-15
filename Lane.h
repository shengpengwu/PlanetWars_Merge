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

using namespace std;

class Lane: public DrawableGeometry
{
public:
    Lane();
    ~Lane();

    vector <Unit *> attackerUnits;
    vector <Unit *> defenderUnits;
    int furthestAttacker;
    int furthestDefender;
    
    void setSelected(bool selected);
    void deployUnit(Unit * unit, bool attacker);
    void advanceUnit(Unit * unit, bool attacker);
    void actUnit(Unit * unit, bool attacker);
    Unit* findFurthestUnit(bool attacker);
    void tick();
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    void compileDL();
    void draw();
};

#endif