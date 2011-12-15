//
//  Unit.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Unit.h"
#include "Model.h"

bool Unit::compiled = false;
GLuint Unit::displayList;

Unit::Unit(void) {
    initThings();
}

Unit::Unit(int type) {
    setType(type);
    initThings();
}

void Unit::initThings()
{
    level = 1;
    pos = 0;
    if(!Unit::compiled) Unit::compileDL();
}

void Unit::reset()
{
    setType(type);
    pos = 0;
}

void Unit::setType(int type) {
	this->type = type;
	switch(type) {
        case TYPE_WATER:
            health = WATER_HEALTH;
            damage = WATER_DAMAGE;
            speed = WATER_SPEED;
            range = WATER_RANGE;
            cooldown = 0;
            this->setColor(WATER_R, WATER_G, WATER_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_EARTH:
            health = EARTH_HEALTH;
            damage = EARTH_DAMAGE;
            speed = EARTH_SPEED;
            range = EARTH_RANGE;
            cooldown = 0;
            this->setColor(EARTH_R, EARTH_G, EARTH_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_WIND:
            health = WIND_HEALTH;
            damage = WIND_DAMAGE;
            speed = WIND_SPEED;
            range = WIND_RANGE;
            cooldown = 0;
            this->setColor(WIND_R, WIND_G, WIND_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_FIRE:
            health = FIRE_HEALTH;
            damage = FIRE_DAMAGE;
            speed = FIRE_SPEED;
            range = FIRE_RANGE;
            cooldown = 0;
            this->setColor(FIRE_R, FIRE_G, FIRE_B, 1.0, 0.1, 0.5, 0.7);
            break;
    }
}

void Unit::resetCooldown()
{
    switch(type) {
        case TYPE_WATER:
            cooldown = WATER_COOL;
            break;
        case TYPE_EARTH:
            cooldown = EARTH_COOL;
            break;
        case TYPE_WIND:
            cooldown = WIND_COOL;
            break;
        case TYPE_FIRE:
            cooldown = FIRE_COOL;
            break;
    }
}

bool Unit::attack(Unit *enemy)
{
    if(cooldown == 0)
    {
        enemy->health -= damage;
        resetCooldown();
    }
    else
        cooldown--;
    return (enemy->health <= 0);
}

void Unit::compileDL()
{
    if(Unit::compiled) return;
    Unit::displayList = glGenLists(1);
    glNewList(Unit::displayList, GL_COMPILE);
    
	gluSphere(gluNewQuadric(), 1, 36, 18);
    
    glEndList();
    Unit::compiled = true;
}

void Unit::draw()
{
    if(!Unit::compiled) return;
    setGLColor();
    glCallList(Unit::displayList);
}

void Unit::drawAtPosition()
{
    glPushMatrix();
    glTranslated(0, 0, pos);
    glPopMatrix();
}









