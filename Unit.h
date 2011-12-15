//
//  Unit.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_UNIT
#define H_UNIT

#include "Model.h"
#include "DrawableGeometry.h"

class Unit : public DrawableGeometry
{
public:

    Unit(void); 
	Unit(int type);
    void initThings();
    
    int pos;
    
    int type;
    int level;
    
    int health;
    int damage;
    int speed;
	int range;
    int cooldown;

    void reset();
    void resetCooldown();
    void setType(int type);
    bool attack(Unit * enemy);

    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    void compileDL();
    void draw();
    void drawAtPosition();
};

#endif