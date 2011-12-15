//
//  Player.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_PLAYER
#define H_PLAYER

class Fleet;
#include "Model.h"
#include "Node.h"

class Player
{
public:    
    Node ** myNodes;
    Node * home;
    Ship** shipArray;
    
    int nodesOwned;
    int waterNodesOwned;
    int earthNodesOwned;
    int windNodesOwned;
    int fireNodesOwned;
    int darkNodesOwned;
    
    int numShips;
    int darkResources;
    
    bool hasNode(Node *node);
    void surrenderNode(Node *node);
    void attackNode(Node *attackNode, Node *defendNode);
    void conquerNode(Node *node);
    void endTurn();
    
    bool hasShip(Ship * s);
    bool addShip(Node * n);
    void purchaseShip();
    void refreshShips();
    
    Player();
    ~Player();
    
    
    
    

    void draw();
};

#endif