//
//  Ship.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_SHIP
#define H_SHIP

#include "Model.h"
#include "DrawableGeometry.h"
#include "Node.h"
#include "Player.h"

class Ship: public DrawableGeometry
{
public:
    Ship(Player * o);
    ~Ship();
    
    int shipType;
    float layer;
    bool done;
    Node * loc;
    Player * owner;
	int health;

	int summonTime;
    
    int numWaterUnits;
    int numEarthUnits;
    int numWindUnits;
    int numFireUnits;
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    
    virtual void compileDL();   //Stores geometry in a displayList
    virtual void draw();        //draws geometry at current location
    void drawCargo();
    void drawAtPosition();

    void moveToNode(Node * newLoc);
    void addUnit(int type);
    Unit * deployUnit(int type);
    
};

#endif