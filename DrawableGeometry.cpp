//
//  DrawableGeometry.cpp
//  MoshBall
//
//  Created by Philip Dougherty on 11/12/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "DrawableGeometry.h"

bool DrawableGeometry::compiled = false;
GLuint DrawableGeometry::displayList;

DrawableGeometry::DrawableGeometry()
{
    if(!compiled) compileDL();
}

DrawableGeometry::~DrawableGeometry()
{
    
}

void DrawableGeometry::compileDL()
{
    //Sample compilation of a simple sphere 
    if(compiled) return;
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);
    setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
    setGLColor();
    gluSphere(gluNewQuadric(),50,50,50);
    glEndList();
    compiled = true;
}

void DrawableGeometry::draw()
{
    if(!compiled) return;
    glCallList(displayList);
}

void DrawableGeometry::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a, float sp, float di, float am)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
    color[3] = a;
    specular[0] = color[0]*sp;
    specular[1] = color[1]*sp;
    specular[2] = color[2]*sp;
    specular[3] = color[3];
    diffuse[0] = color[0]*di;
    diffuse[1] = color[1]*di;
    diffuse[2] = color[2]*di;
    diffuse[3] = color[3];
    ambient[0] = color[0]*am;
    ambient[1] = color[1]*am;
    ambient[2] = color[2]*am;
    ambient[3] = color[3];
    
}

void DrawableGeometry::setGLColor()
{
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);  
    glColor4d(color[0], color[1], color[2], color[3]);
}