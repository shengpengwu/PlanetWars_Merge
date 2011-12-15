//
//  Menu.h
//  SpongeBobWars
//
//  Created by Brandon Lewis on 11/30/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_MENU
#define H_MENU

#include "Model.h"
#include "DrawableGeometry.h"

class Menu: public DrawableGeometry
{
public:
    //GL Vars
	static bool compiled;
	static GLuint displayList;
    void draw();

	// Fuctions:
	Menu();
	~Menu();
    
	void setMenu(int menu);
	void flipFlag();
	bool getFlag();
	

private:
	// Menu variables:
	bool menuFlag;
	void setTitle();
	void setMain();
	void setMetaPause();
	void setMiniPause();
	void compileDL();
};

#endif