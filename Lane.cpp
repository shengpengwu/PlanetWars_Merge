//
//  Lane.cpp
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Lane.h"

//DRAWABLE GEOMETRY STUFF
bool Lane::compiled = false;
GLuint Lane::displayList;

Lane::Lane()
{
    if(!Lane::compiled) Lane::compileDL();
    setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
    
    furthestAttacker = 0;
    furthestDefender = 0;
}

Lane::~Lane()
{
    
}

void Lane::compileDL()
{
    if(Lane::compiled) return;
    Lane::displayList = glGenLists(1);
    glNewList(Lane::displayList, GL_COMPILE);
    
    glBegin(GL_QUADS);	
    
    glVertex3f(-1*LANE_WIDTH/2.0, -1, -1*LANE_LENGTH/2.0);
	glVertex3f(LANE_WIDTH/2.0, -1, -1*LANE_LENGTH/2.0);
	glVertex3f(LANE_WIDTH/2.0, -1, LANE_LENGTH/2.0);
	glVertex3f(-1*LANE_WIDTH/2.0, -1, LANE_LENGTH/2.0);
    
	glEnd();
    
    glEndList();
    Lane::compiled = true;
}

void Lane::draw()
{
    if(!Lane::compiled) return;
    setGLColor();
    glCallList(Lane::displayList);
    
    for(int i = 0; i < attackerUnits.size(); i++)
        attackerUnits[i]->drawAtPosition();
    for(int i = 0; i < defenderUnits.size(); i++)
        defenderUnits[i]->drawAtPosition();
}

//LOGIC STUFF
void Lane::setSelected(bool selected)
{
    if(selected)
        setColor(0.1, 0.2, 0.8, 0.0, 0.5, 1.0, 1.0);
    else
        setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);
}

void Lane::deployUnit(Unit * unit, bool attacker)
{
    if(attacker)
    {
        attackerUnits.resize(attackerUnits.size()+1);
        attackerUnits[attackerUnits.size()-1] = unit;
    }
    else
    {
        defenderUnits.resize(defenderUnits.size()+1);
        defenderUnits[defenderUnits.size()-1] = unit;
    }
}

void Lane::advanceUnit(Unit * unit, bool attacker)
{
    if(attacker)
    {
        if(unit->pos+unit->speed > LANE_LENGTH-furthestDefender)
            unit->pos = furthestAttacker;
        else
            unit->pos = unit->pos+unit->speed;
        
        if(unit->pos > furthestAttacker) furthestAttacker = unit->pos;
    }
    else
    {
        if(unit->pos+unit->speed > LANE_LENGTH-furthestAttacker)
            unit->pos = furthestAttacker;
        else
            unit->pos = unit->pos+unit->speed;
        
        if(unit->pos > furthestDefender) furthestDefender = unit->pos;
    }
}

void Lane::actUnit(Unit * unit, bool attacker)
{
    bool kill;
    if(attacker)
    {
        if(defenderUnits.size() != 0)
        {
            if(unit->pos+unit->range >= LANE_LENGTH-furthestDefender)
            {
                kill = unit->attack(findFurthestUnit(false));
                if(kill)
                {
                    delete defenderUnits[defenderUnits.size()];
                    defenderUnits.resize(defenderUnits.size()-1);
                    if(defenderUnits.size() == 0)
                        furthestDefender = 0;
                    else
                        furthestDefender = findFurthestUnit(false)->pos;
                }
            }
        }
        else
        {
            //Attack Ship
        }
    }
    else
    {
        if(unit->pos+unit->range >= LANE_LENGTH-furthestAttacker)
        {
            if(attackerUnits.size() != 0)
            {
                kill = unit->attack(findFurthestUnit(true));
                if(kill)
                {
                    delete attackerUnits[attackerUnits.size()];
                    attackerUnits.resize(attackerUnits.size()-1);
                    if(attackerUnits.size() == 0)
                        furthestAttacker = 0;
                    else
                        furthestAttacker = findFurthestUnit(true)->pos;
                }
            }
            else
            {
                //Attack Ship
            }
        }
    }
}

Unit* Lane::findFurthestUnit(bool attacker)
{
    int furthestPos = -1;
    Unit * u;
    if(attacker)
    {
        for(int i = 0; i < attackerUnits.size(); i++)
        {
            if(attackerUnits[i]->pos > furthestPos)
            {
                furthestPos = attackerUnits[i]->pos;
                u = attackerUnits[i];
            }
        }
    }
    else
    {
        for(int i = 0; i < defenderUnits.size(); i++)
        {
            if(defenderUnits[i]->pos > furthestPos)
            {
                furthestPos = defenderUnits[i]->pos;
                u = defenderUnits[i];
            }
        }
    }
    
    return u;
}

void Lane::tick()
{
    //Update Units' Positions
    for(int i = 0; i < defenderUnits.size(); i++)
    {
        advanceUnit(defenderUnits[i], false);
    }
    for(int i = 0; i < attackerUnits.size(); i++)
    {
        advanceUnit(attackerUnits[i], true);
    }
    
    //Attack Units
    for(int i = 0; i < defenderUnits.size(); i++)
    {
        actUnit(defenderUnits[i], false);
    }
    for(int i = 0; i < attackerUnits.size(); i++)
    {
        actUnit(attackerUnits[i], true);
    }
}