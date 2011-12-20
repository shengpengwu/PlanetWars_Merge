//
//  Node.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_NODE
#define H_NODE

#include <math.h>
#include "Model.h"
#include "Player.h"
#include "Ship.h"
#include "DrawableGeometry.h"

class Node: public DrawableGeometry
{
public:
    //Water, Earth, Wind, Fire
    int type;
    void setType(int t);
    
    //Used for information in linking/positioning
    int row;
    int column;
    int djikRating; //Used for Djikstra's
    bool selected;
    bool display; //<- only used by Hud
    
    Player * owner;
    Ship * ship;
    
    int numNeighborNodes;
    Node ** neighborNodes; 
    //Mapping of array to neighbor:
    //neighborNodes[0] = top;
    //neighborNodes[1] = topRight;
    //neighborNodes[2] = bottomRight;
    //neighborNodes[3] = bottom;
    //neighborNodes[4] = bottomLeft;
    //neighborNodes[5] = topLeft;
    
    void initStuff();
    Node();
    Node(int type);
    ~Node();
    Node * findFirstStep();
    void setNeighborDjikWhileSearchingFor(Node * destination);
    int getRandomFreeNeighbor();
    int getRandomNeighbor();
    void assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft);
    bool isOpenNeighborOf(Node * n);
    bool isNeighborOf(Node * n);
    void select(bool select);
    void tick(); //Do whatever needs to be done on the passing of a turn
    
    //Drawable Geometry Stuff
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    static GLuint typDList;
    static GLuint ownDList;
    static GLuint homDList;
    void compileDL();
    void draw();
    void drawAtPosition();
};

#endif