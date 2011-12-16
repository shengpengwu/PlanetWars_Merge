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

Lane::Lane(Ship* atkShip, Ship* defShip)
{
	if(!Lane::compiled) Lane::compileDL();
	setColor(0.9, 0.5, 0.3, 0.0, 0.5, 1.0, 1.0);

	furthestAttacker = 0;
	furthestDefender = 0;
	attackShip = atkShip;	
	defendShip = defShip;
	atkSummonTime = 0;
	defSummonTime = 0;
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

	glPushMatrix();	glRotated(180.0, 0.0, 1.0, 0.0);
	glTranslated(0.0, 0.0, -LANE_LENGTH/2.0);   
	for(int i = 0; i < attackerUnits.size(); i++)
		attackerUnits[i]->drawAtPosition();
	glPopMatrix();	glPushMatrix();	glTranslated(0.0, 0.0, -LANE_LENGTH/2.0);  
	for(int i = 0; i < defenderUnits.size(); i++)
		defenderUnits[i]->drawAtPosition();
	glPopMatrix();}

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
		
		if(atkSummonTime <= 0) { 
			attackerUnits.resize(attackerUnits.size()+1);
			attackerUnits[attackerUnits.size()-1] = unit;
			atkSummonTime = SUMMON_TIME;	
		}        
	}
	else
	{
		if(defSummonTime <= 0) {
			defenderUnits.resize(defenderUnits.size()+1);
			defenderUnits[defenderUnits.size()-1] = unit;	
			defSummonTime = SUMMON_TIME;	
		}        
	}
}

void Lane::advanceUnit(Unit * unit, bool attacker)
{

    if(attacker)
    { 

		Unit* nextHealUnit = findNextHeal(true);

		if(unit->pos+unit->range  > LANE_LENGTH-furthestDefender){
            //unit->pos = furthestDefender;
		}
		else if(nextHealUnit != Model::getSelf()->nullUnit && unit->type == 0 && unit->pos+unit->range > nextHealUnit->pos) {

		}
        else
            unit->pos = unit->pos+unit->speed;
        
        if(unit->pos > furthestAttacker) furthestAttacker = unit->pos;
    }
    else
    {

		Unit* nextHealUnit = findNextHeal(false);

		if(unit->pos+unit->range > LANE_LENGTH-furthestAttacker){
           //unit->pos = furthestAttacker;
		}
		else if(nextHealUnit != Model::getSelf()->nullUnit && unit->type == 0 && unit->pos+unit->range > nextHealUnit->pos) {

		}
        else
           unit->pos = unit->pos+unit->speed;
        
        if(unit->pos > furthestDefender) furthestDefender = unit->pos;
    }	
}


void Lane::actUnit(Unit * unit, bool attacker)
{
    bool kill;

	//attacker
    if(attacker)
    {
		//if unit is healer and within range of friendly, heal
		if(findNextHeal(true) != Model::getSelf()->nullUnit)
		{
			if(unit->pos+unit->speed+unit->range >= findNextHeal(true)->pos)
            {				
				unit->healUnit(findNextHeal(true));
            }
		}

		//if unit is within range of an enemy, attack    
		if(unit->pos+unit->speed+unit->range >= LANE_LENGTH-furthestDefender)        
        {
			if(defenderUnits.size() != 0)
			        
            {				
                kill = unit->attack(findFurthestUnit(false));
                if(kill)
                {
					//use vector.erase() with index in array
					defenderUnits.erase( defenderUnits.begin() + getIndex(defenderUnits, findFurthestUnit(false)));

                    //delete defenderUnits[defenderUnits.size()];
                    //defenderUnits.resize(defenderUnits.size()-1);
                    if(defenderUnits.size() == 0)
                        furthestDefender = 0;
                    else
                        furthestDefender = findFurthestUnit(false)->pos;
                }
            }





        }
        else if(unit->pos+unit->speed+unit->range >= LANE_LENGTH) 
        {
			//Attack Ship
			kill = unit->attackShip(defendShip);

			if(kill) {
				//end game
				//MessageBox(NULL, "Defend ship is dead!", NULL, NULL);
			}
            
        }
    }

	//defender
    else
    {

		//if unit is healer and within range of friendly, heal
		if(findNextHeal(false) != Model::getSelf()->nullUnit)
		{
			if(unit->pos+unit->speed+unit->range >= findNextHeal(false)->pos)
            {				
				unit->healUnit(findNextHeal(false));
            }
		}

		//if unit is within range of an enemy, attack
        if(unit->pos+unit->speed+unit->range >= LANE_LENGTH-furthestAttacker)
        {
            if(attackerUnits.size() != 0)
            {
                kill = unit->attack(findFurthestUnit(true));
				if(kill)
				{
					//use vector.erase() with index in array
					attackerUnits.erase( attackerUnits.begin() + getIndex(attackerUnits, findFurthestUnit(true)) );
					//delete attackerUnits[attackerUnits.size()];
					//attackerUnits.resize(attackerUnits.size()-1);
					if(attackerUnits.size() == 0)
						furthestAttacker = 0;
					else
						furthestAttacker = findFurthestUnit(true)->pos;
				}
			}


		}
		else if(unit->pos+unit->speed+unit->range >= LANE_LENGTH)
		{
			//Attack Ship
			kill = unit->attackShip(attackShip);

			if(kill) {
				//end game
				//MessageBox(NULL, "Attack ship is dead!", NULL, NULL);
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

Unit* Lane::findNextHeal(bool attacker){
	int closestPos = 1000000;
	Unit * x = Model::getSelf()->nullUnit;  
	if(attacker)  
	{      
		for(int i = 0; i < attackerUnits.size(); i++)     
		{		
			if(attackerUnits[i]->pos < closestPos && attackerUnits[i]->health < attackerUnits[i]->maxHealth && attackerUnits[i]->type != 0)   
			{     
				closestPos = attackerUnits[i]->pos;      
				x = attackerUnits[i];     
			}   
		}  
	}   
	else   
	{    
		for(int i = 0; i < defenderUnits.size(); i++)  
		{		
			if(defenderUnits[i]->pos < closestPos && defenderUnits[i]->health < defenderUnits[i]->maxHealth && defenderUnits[i]->type != 0)  
			{           
				closestPos = defenderUnits[i]->pos;     
				x = defenderUnits[i]; 
			}   
		}  
	}      
	return x;
}

void Lane::tick()
{
	atkSummonTime--;	defSummonTime--;    //Update Units' Positions
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
		defenderUnits[i]->update();    }
	for(int i = 0; i < attackerUnits.size(); i++)
	{
		actUnit(attackerUnits[i], true);
		attackerUnits[i]->update();  
	}

}

int Lane::getIndex(vector<Unit*> list, Unit* unit)
{	
	for(int i = 0; i < list.size(); i++ )
	{		
		if(list[i] == unit) 
		{			
			return i;		
		}	
	}	
	return -1;
}