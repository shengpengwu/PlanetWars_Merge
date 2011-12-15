//
//  Selector.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/28/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#ifndef SELECTOR_H
#define SELECTOR_H

#include "Model.h"
#include "DrawableGeometry.h"
#include <math.h>

class Selector: public DrawableGeometry
{
public:
    Selector();
    ~Selector();
    
    int column;
    int row;
    float dotX;
    float dotY;
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    static GLuint dot;
    
    void compileDL();       //Stores geometry in a displayList
    void draw();            //draws geometry at current location
    void drawDot();
    void set(float x, float y); //sets row/column based on mouse x and y
    void drawAtPosition();

};

#endif