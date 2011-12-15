//
//  Node.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//


#include "Node.h"

void Node::initStuff()
{
    this->neighborNodes = new Node*[6];
    Node *  nN = Model::getSelf()->nullNode;
    assignNeighbors(nN, nN, nN, nN, nN, nN);
    this->numNeighborNodes = 0;
    owner = Model::getSelf()->nullPlayer;
    ship = Model::getSelf()->nullShip;
    row = NULL_LOCATION;
    column = NULL_LOCATION;
    layer = 0.0f;
    selected = false;
    display = false;
    
    if(!Node::compiled) Node::compileDL();
}

Node::Node()
{
    setType(-1);
    initStuff();
}

Node::Node(int type)
{
    setType(type);
    initStuff();
}

Node::~Node()
{
    delete neighborNodes;
}

void Node::setType(int t)
{
    this->type = t;

    switch (t) {
        case TYPE_EARTH:
            this->setColor(EARTH_R, EARTH_G, EARTH_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_WIND:
            this->setColor(WIND_R, WIND_G, WIND_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_FIRE:
            this->setColor(FIRE_R, FIRE_G, FIRE_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_WATER:
            this->setColor(WATER_R, WATER_G, WATER_B, 1.0, 0.1, 0.5, 0.7);
            break;
        case TYPE_DARK:
            this->setColor(DARK_R, DARK_G, DARK_B, 1.0, 0.1, 0.5, 0.7);
            break;
        default:
            this->setColor(0.3, 0.3, 0.3, 1.0, 0.1, 0.5, 0.7);
            break;
    }
}

int Node::getRandomFreeNeighbor()
{
    int r = (int)(Model::random()*6);
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] == Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

int Node::getRandomNeighbor()
{
    int r = (int)(Model::random()*6);
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] != Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

void Node::assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft)
{
    this->neighborNodes[0] = top;
    this->neighborNodes[1] = topRight;
    this->neighborNodes[2] = bottomRight;
    this->neighborNodes[3] = bottom;
    this->neighborNodes[4] = bottomLeft;
    this->neighborNodes[5] = topLeft;
}

bool Node::isNeighborOf(Node * n)
{
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[i] == n)
            return true;
    }
    return false;
}

void Node::select(bool select)
{
    if(selected && select) return;
    selected = select;
    if(selected)
    {
        if(Model::getSelf()->selectedNode != Model::getSelf()->nullNode)
            Model::getSelf()->selectedNode->select(false);
        Model::getSelf()->selectedNode = this;        
    }
    else
    {
        Model::getSelf()->selectedNode = Model::getSelf()->nullNode;
    }
}

void Node::tick()
{
    if(owner == Model::getSelf()->nullPlayer) return;
    if(this->ship != Model::getSelf()->nullShip) 
        if(!this->ship->done)this->ship->addUnit(type);
    if(owner->home == this) owner->darkResources++;
}


//DRAWABLE GEO FUNCTIONS
bool Node::compiled = false;
GLuint Node::displayList;
GLuint Node::typDList;
GLuint Node::ownDList;
GLuint Node::homDList;

void Node::compileDL()
{
    if(Node::compiled) return;
    
    float sqrtOfThreeOverTwo = sqrt(3.0/2.0);

    Node::displayList = glGenLists(1);
    glNewList(Node::displayList, GL_COMPILE);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(0, layer, 0);
    glVertex3f(1, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);

    glVertex3f(0, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-1, layer, 0);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-1, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    
    glVertex3f(0, layer, 0);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    glVertex3f(1, layer, 0);
    glEnd();
    
    glEndList();
    
    
    
    
    
    Node::typDList = glGenLists(1);
    glNewList(Node::typDList, GL_COMPILE);
    
    glPushMatrix();
    glScalef(0.9, 1.0, 0.9);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, layer+0.05, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer+0.05, -1*sqrtOfThreeOverTwo); 
    glVertex3f(-1, layer+0.05, 0);
    glEnd();
    
    glTranslated(0.0, -0.075, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, layer, 0);
    glVertex3f(1, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-0.5, layer, sqrtOfThreeOverTwo);
    glVertex3f(-1, layer, 0);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-1, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer, 0);
    glVertex3f(-0.5, layer, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    
    glVertex3f(0, layer, 0);
    glVertex3f(0.5, layer, -1*sqrtOfThreeOverTwo);  
    glVertex3f(1, layer, 0);
    glEnd();
    glPopMatrix();
    
    glEndList();
    
    
    
    
    Node::ownDList = glGenLists(1);
    glNewList(Node::ownDList, GL_COMPILE);
    
    glPushMatrix();
    glScalef(0.6, 1.0, 0.6);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, layer+0.1, 0);
    glVertex3f(1, layer+0.1, 0);
    glVertex3f(0.5, layer+0.1, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer+0.1, 0);
    glVertex3f(0.5, layer+0.1, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer+0.1, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer+0.1, 0);
    glVertex3f(-0.5, layer+0.1, sqrtOfThreeOverTwo);
    glVertex3f(-1, layer+0.1, 0);
    
    glVertex3f(0, layer+0.1, 0);
    glVertex3f(-1, layer+0.1, 0);
    glVertex3f(-0.5, layer+0.1, -1*sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer+0.1, 0);
    glVertex3f(-0.5, layer+0.1, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer+0.1, -1*sqrtOfThreeOverTwo);  
    
    glVertex3f(0, layer+0.1, 0);
    glVertex3f(0.5, layer+0.1, -1*sqrtOfThreeOverTwo);  
    glVertex3f(1, layer+0.1, 0);
    glEnd();
    glPopMatrix();
    
    glEndList();
    
    
    
    
    
    
    Node::homDList = glGenLists(1);
    glNewList(Node::homDList, GL_COMPILE);
    
    glPushMatrix();
    glScalef(1.2, 1.0, 1.2);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, layer-0.01, 0);
    glVertex3f(1, layer-0.01, 0);
    glVertex3f(0.5, layer-0.01, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer-0.01, 0);
    glVertex3f(0.5, layer-0.01, sqrtOfThreeOverTwo);
    glVertex3f(-0.5, layer-0.01, sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer-0.01, 0);
    glVertex3f(-0.5, layer-0.01, sqrtOfThreeOverTwo);
    glVertex3f(-1, layer-0.01, 0);
    
    glVertex3f(0, layer-0.01, 0);
    glVertex3f(-1, layer-0.01, 0);
    glVertex3f(-0.5, layer-0.01, -1*sqrtOfThreeOverTwo);
    
    glVertex3f(0, layer-0.01, 0);
    glVertex3f(-0.5, layer-0.01, -1*sqrtOfThreeOverTwo);
    glVertex3f(0.5, layer-0.01, -1*sqrtOfThreeOverTwo);  
    
    glVertex3f(0, layer-0.01, 0);
    glVertex3f(0.5, layer-0.01, -1*sqrtOfThreeOverTwo);  
    glVertex3f(1, layer-0.01, 0);
    glEnd();
    glPopMatrix();
    
    glEndList();
     
    

    Node::compiled = true;
}

void Node::draw()
{
    if(!Node::compiled) return;
    if(owner != Model::getSelf()->nullPlayer)
    {
        if(owner->home == this || display) // <- 'display' is only for the hud
        {
            if(owner == Model::getSelf()->playerArray[0])
                setColor(PLAYER_1_R, PLAYER_1_G, PLAYER_1_B, 1.0f, 0.1f, 0.5f, 0.7);
            else
                setColor(PLAYER_2_R, PLAYER_2_G, PLAYER_2_B, 1.0f, 0.1f, 0.5f, 0.7);
            setGLColor();
            glCallList(Node::homDList);
        }
    }
    if(selected)
    {
        float color;
        color = (sinf((float)(Model::getSelf()->tickCount/200.0))/2+.5)/2 + .5;
        if(color < 0.5f) color = 0.5f;
        setColor(color, color, color, 1.0, 1.0, 1.0, 1.0);
    }
    else
        setColor(0.3, 0.3, 0.3, 1.0, 0.1, 0.5, 0.7);
    setGLColor();
    glCallList(Node::displayList);
    setType(type);
    setGLColor();
    glCallList(Node::typDList);
    if(owner != Model::getSelf()->nullPlayer)
    {
        if(owner == Model::getSelf()->playerArray[0])
            setColor(PLAYER_1_R+0.4, PLAYER_1_G+0.4, PLAYER_1_B+0.4, 1.0f, 0.1f, 0.5f, 0.7);
        else
            setColor(PLAYER_2_R+0.4, PLAYER_2_G+0.4, PLAYER_2_B+0.4, 1.0f, 0.1f, 0.5f, 0.7);
        setGLColor();
        glCallList(Node::ownDList);
    }
}

void Node::drawAtPosition()
{
    glPushMatrix();
    glTranslated(column*COL_SPACING, 0, row*ROW_SPACING);
    draw();
    glPopMatrix();
}