//
//  Map.h
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef MAP_H
#define MAP_H

#include "Model.h"
#include "Node.h"
#include "Selector.h"

class Map
{
public:
    Node ** nodeArray;
    Node ** djikQueue;
    int djikQIndex;
    int djikQLen;
    bool djikFound;
    Selector * selector;
    
    Map(int numNodes);
    ~Map();
    
    Node * getNodeAt(int row, int col);
    void selectSelected();
    void djikEnqueNode(Node * node);
    Node * findNextDjikNodFromAtoB(Node * a, Node * b);
    void linkNodeToNeighbors(Node * node);
    void createNodeMap(int numNodes);
    void tick();
    void draw();
};
#endif