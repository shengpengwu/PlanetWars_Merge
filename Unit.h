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

private:
	int type;

public:

    Unit(void); 
	Unit(int type);
    void initThings();


	int arrayIndex;
    
    int pos;
    
    
    int level;
	bool attacker;
    
	int maxHealth;
    int health;
    int damage;
    int speed;
	int range;
    int cooldown;
	int healCooldown;
	int convertCooldown;
	int healVal;

	int getType();
    void reset();
    void resetCooldown();
	void resetHeal();
    void setType(int type);
    bool attack(Unit * enemy);
	bool attackShip(Ship *atkShip);
	bool healUnit(Unit * friendly);
	void setAttacker(bool attackerVal);
	void resetConvert();

    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    static GLuint healthBar;
    void compileDL();
	void update();
    void draw();
    void drawAtPosition();
};

#endif