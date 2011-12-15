
//
//  Ship.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Ship.h"
#include "Model.h"
bool Ship::compiled = false;
GLuint Ship::displayList;

Ship::Ship(Player * o)
{
    this->shipType = SHIP_TYPE_GENERIC;
    layer = .25;
    owner = o;
    numWaterUnits = 0;
    numEarthUnits = 0;
    numWindUnits = 0; 
    numFireUnits = 0;
    done = false;
    if(!Ship::compiled) compileDL();
	health = 20000;
	//summonTime = SUMMON_TIME;
}

Ship::~Ship()
{
    
}

void Ship::compileDL()
{

    //Sample compilation of a simple sphere 
    if(Ship::compiled) return;
    displayList = glGenLists(1);
    glNewList(Ship::displayList, GL_COMPILE);
    
    //Set Color Here
    setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
    setGLColor();

    //DRAW SHIP HERE
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glVertex3f(-.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3f(-.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3d(SHIP_SIZE, layer, 0);
    glVertex3d(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glEnd();
    
    setColor(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
    setGLColor();
    glPushMatrix();
    glScalef(0.6, 1.0, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(-.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3f(-.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3d(SHIP_SIZE+0.2, layer, 0);
    glVertex3d(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glEnd();
    glPopMatrix();
    
    glPopMatrix();
    
    glEndList();
    Ship::compiled = true;
}

void Ship::draw()
{
    if(!Ship::compiled) return;  
    float red;
    float blue;
    float don;
    if(owner == Model::getSelf()->playerArray[0])
    {
        red = 0.4;
        blue = 0;
    }
    else
    {
        red = 0;
        blue = 0.4;
    }
    if(done) don = -0.4;
    else don = 0;
        
    setColor(0.2+red+don, 0.2+don, 0.2+blue+don, 1.0, 1.0, 1.0, 1.0);
    setGLColor();
    glCallList(Ship::displayList);
    drawCargo();
}

void Ship::drawCargo()
{
    double h;
    glPushMatrix();
    glScalef(0.6, 1.0, 0.6);
    
    if(numWaterUnits>0)
        h = 5;
    //Draw Water
    setColor(WATER_R, WATER_G, WATER_B, 1.0, 0.1, 0.5, 0.7);
    setGLColor();
    h = (float)numWaterUnits/(float)MAX_UNITS;
    if(h > 0)
    {
        glBegin(GL_QUADS);
        glVertex3f(-.5*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE);
        glVertex3f(-.5*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(-.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(-.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE);
        glEnd();
    }
    
    //Draw Earth
    setColor(EARTH_R, EARTH_G, EARTH_B, 1.0, 0.1, 0.5, 0.7);
    setGLColor();
    h = (float)numEarthUnits/(float)MAX_UNITS;
    if(h > 0)
    {
        glBegin(GL_QUADS);
        glVertex3f(-.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE);
        glVertex3f(-.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(0, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(0, layer+0.1, .5*SHIP_SIZE);
        glEnd();
    }
    
    //Draw Wind
    setColor(WIND_R, WIND_G, WIND_B, 1.0, 0.1, 0.5, 0.7);
    setGLColor();
    h = (float)numWindUnits/(float)MAX_UNITS;
    if(h > 0)
    {
        glBegin(GL_QUADS);
        glVertex3f(0, layer+0.1, .5*SHIP_SIZE);
        glVertex3f(0, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE);
        glEnd();
    }
    
    //Draw Fire
    setColor(FIRE_R, FIRE_G, FIRE_B, 1.0, 0.1, 0.5, 0.7);
    setGLColor();
    h = (float)numFireUnits/(float)MAX_UNITS;
    if(h > 0)
    {
        glBegin(GL_QUADS);
        glVertex3f(.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE);
        glVertex3f(.25*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(.5*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE-(h*SHIP_SIZE));
        glVertex3f(.5*SHIP_SIZE, layer+0.1, .5*SHIP_SIZE);
        glEnd();
    }
    
    glPopMatrix();
}

void Ship::drawAtPosition()
{
    if(loc == Model::getSelf()->nullNode)
    {
        draw();
        return;
    }
    glPushMatrix();
    glTranslated(loc->column*COL_SPACING, 0, loc->row*ROW_SPACING);
    draw();
    glPopMatrix();
}

void Ship::moveToNode(Node *newLoc)
{
    if(done) return;
    if(loc->isNeighborOf(newLoc))
    {
        loc->ship = Model::getSelf()->nullShip;
        loc = newLoc;
        loc->ship = this;
        done = true;
        this->owner->conquerNode(loc);
    }
}

void Ship::addUnit(int type)
{
    switch(type)
    {
        case TYPE_WATER:
            if(numWaterUnits+owner->waterNodesOwned >= MAX_UNITS) numWaterUnits = MAX_UNITS;
            else numWaterUnits+=owner->waterNodesOwned;
            break;
        case TYPE_EARTH:
            if(numEarthUnits+owner->earthNodesOwned >= MAX_UNITS) numEarthUnits = MAX_UNITS;
            else numEarthUnits+=owner->earthNodesOwned;
            break;
        case TYPE_WIND:
            if(numWindUnits+owner->windNodesOwned >= MAX_UNITS) numWindUnits = MAX_UNITS;
            else numWindUnits+=owner->windNodesOwned;
            break;
        case TYPE_FIRE:
            if(numFireUnits+owner->fireNodesOwned >= MAX_UNITS) numFireUnits = MAX_UNITS;
            else numFireUnits+=owner->fireNodesOwned;
            break;
        case TYPE_DARK:
            owner->darkResources+=owner->darkNodesOwned;
            break;
        default:
            break;
    }
}

Unit * Ship::deployUnit(int type)
{
    switch(type)
    {
        case TYPE_WATER:
            if(numWaterUnits <= 0) break;
            numWaterUnits--;
            return new Unit(TYPE_WATER);
            break;
        case TYPE_EARTH:
            if(numEarthUnits >= MAX_UNITS) break;
            numEarthUnits--;
            return new Unit(TYPE_EARTH);
            break;
        case TYPE_WIND:
            if(numWindUnits >= MAX_UNITS) break;
            numWindUnits--;
            return new Unit(TYPE_WIND);
            break;
        case TYPE_FIRE:
            if(numFireUnits >= MAX_UNITS) break;
            numFireUnits--;
            return new Unit(TYPE_FIRE);
            break;
        default:
            break;
    }
    return Model::getSelf()->nullUnit;
}