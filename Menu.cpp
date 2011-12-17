//
//  Menu.cpp
//  SpongeBobWars
//
//  Created by Brandon Lewis on 11/30/2011
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Menu.h"
#include "Textprint.h"

bool Menu::compiled = false;
GLuint Menu::displayList;

// Building the different kinds of menues for display:

Menu::Menu()
{
    layer = 1.0f;
    setColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0); // Base color
    if(!Menu::compiled) Menu::compileDL();
}

Menu::~Menu()
{

}

// Different types of menu:
void Menu::setTitle(){
	menuFlag = true;
    setColor(.81, .194, .7212, 1.0, 1.0, 1.0, 1.0);
	TextPrint().bitText(-13,2,-10,0.3,0.3,0.3,GLUT_BITMAP_TIMES_ROMAN_24, "Welcome to Planet Wars");

}

void Menu::setMain(){
	menuFlag = true;
    setColor(.9, .7, .8, 1.0, 1.0, 1.0, 1.0);
}

void Menu::setMetaPause(){
	menuFlag = true;
    setColor(.323, .321, .321, 1.0, 1.0, 1.0, 1.0);
}

void Menu::setMiniPause(){
	menuFlag = true;
    setColor(.431, .61, .71, 1.0, 1.0, 1.0, 1.0);
}


// Changes to the specified menu, calling this will pause all game actions until the player presses resume.
// This is also going to compile the menu, so everything should be controlled using this and the flag functions.
void Menu::setMenu(int menu){
	switch (menu){
	case TITLE:
		setTitle();
		break;
	case MAIN:
		setMain();
		break;
	case MINI:
		setMiniPause();
		break;
	case META:
		setMetaPause();
	}
}

// Resets the flage and turns off the menu display.
void Menu::flipFlag(){
	menuFlag = false;
}

bool Menu::getFlag(){
	return this->menuFlag;
}

void Menu::draw(){
    if(!Menu::compiled || !menuFlag) return;
    setGLColor();
    glCallList(Menu::displayList);
}

void Menu::compileDL()
{
    if(Menu::compiled) return;
    Menu::displayList = glGenLists(1);
	glDisable(GL_LIGHTING);
    glPushMatrix();
    glNewList(Menu::displayList, GL_COMPILE);
    
    glBegin(GL_QUADS);
    
    glVertex3f(-1, layer, -1);
	glVertex3f(-1, layer, 1);
	glVertex3f(1, layer, 1);
    glVertex3f(1, layer, -1);
    
    glEnd();
    glPopMatrix();
    glEndList();
	Menu::compiled = true;

}