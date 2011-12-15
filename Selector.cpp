//
//  Selector.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/12/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include <math.h>
#include "Selector.h"

bool Selector::compiled = false;
GLuint Selector::displayList;
GLuint Selector::dot;

Selector::Selector()
{
    layer = -.1f;
    setColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    row = 0;
    column = 0;
    if(!Selector::compiled) Selector::compileDL();
}

Selector::~Selector()
{
    
}

void Selector::compileDL()
{
    if(Selector::compiled) return;
    float sqrtOfThreeOverTwo = sqrt(3.0/2.0);
    
    Selector::displayList = glGenLists(1);
    glNewList(Selector::displayList, GL_COMPILE);
    
    glPushMatrix();
    glScalef(1.1f, 1.0f, 1.1f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, layer, 0.0);
    glVertex3f(1.0, layer, 0.0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0.0, layer, 0.0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0.0, layer, 0.0);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-1.0, layer, 0.0);
    
    glVertex3f(0.0, layer, 0.0);
    glVertex3f(-1.0, layer, 0.0);
    glVertex3f(-0.5, layer, -1.0*sqrtOfThreeOverTwo);
    
    glVertex3f(0.0, layer, 0.0);
    glVertex3f(-0.5, layer, -1.0*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer, -1.0*sqrtOfThreeOverTwo);  
    
    glVertex3f(0.0, layer, 0.0);
    glVertex3f(0.5, layer, -1.0*sqrtOfThreeOverTwo);  
    glVertex3f(1.0, layer, 0.0);
    glEnd();
    glPopMatrix();
    
    glEndList();   
    
    
    
    
    Selector::dot = glGenLists(1);
    glNewList(Selector::dot, GL_COMPILE);
    
    glPushMatrix();
    glScalef(0.1f, 1.0f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, layer+.22f, 0.0);
    glVertex3f(1.0, layer+.22f, 0.0);
    glVertex3f(0.5, layer+.22f, sqrtOfThreeOverTwo);
    
    glVertex3f(0.0, layer+.22f, 0.0);
    glVertex3f(0.5, layer+.22f, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer+.22f, sqrtOfThreeOverTwo);
    
    glVertex3f(0.0, layer+.22f, 0.0);
    glVertex3f(-0.5, layer+.22f, sqrtOfThreeOverTwo);
    glVertex3f(-1.0, layer+.22f, 0.0);
    
    glVertex3f(0.0, layer+.22f, 0.0);
    glVertex3f(-1.0, layer+.22f, 0.0);
    glVertex3f(-0.5, layer+.22f, -1.0*sqrtOfThreeOverTwo);
    
    glVertex3f(0.0, layer+.22f, 0.0);
    glVertex3f(-0.5, layer+.22f, -1.0*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer+.22f, -1.0*sqrtOfThreeOverTwo);  
    
    glVertex3f(0.0, layer+.22f, 0.0);
    glVertex3f(0.5, layer+.22f, -1.0*sqrtOfThreeOverTwo);  
    glVertex3f(1.0, layer+.22f, 0.0);
    glEnd();
    glPopMatrix();
    
    glEndList(); 
    
    
    
    
    Selector::compiled = true;
}

void Selector::draw()
{
    if(!Selector::compiled) return;
    setColor(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    setGLColor();
    glCallList(Selector::displayList);
}

void Selector::drawDot()
{
    if(!Selector::compiled) return;
    setColor(1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
    setGLColor();
    glCallList(Selector::dot);
}

void Selector::set(float x, float y)
{
    dotX = -Model::getSelf()->zoom*x/2;
    dotY = Model::getSelf()->zoom*y/2;
    int tempC = (int)floor(dotX+.5);
    int tempR = (int)floor(dotY+.5);
    if((tempC + tempR)%2 == 0)
    {
        this->column = tempC;
        this->row = tempR;
    }
    //Uncomment For Debugging:
    //cout << dotX << "\t" << dotY << "\t-\t" << column << "\t" << row << endl;
}

void Selector::drawAtPosition()
{
    glPushMatrix();
    glTranslated(column*COL_SPACING, 0, row*ROW_SPACING);
    draw();
    glPopMatrix();
    glPushMatrix();
    glTranslated(dotX*COL_SPACING, 0, dotY*ROW_SPACING);
    drawDot();
    glPopMatrix();
}