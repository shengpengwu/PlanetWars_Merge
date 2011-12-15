//
//  Model.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#include "Model.h"

Model * Model::selfPtr = NULL;

Model::Model()
{
    if(Model::selfPtr)
        throw (new std::string("DO NOT CALL CONSTRUCTOR DIRECTLY. USE Model::getSelf()"));

    tickCount = 0;
    
    this->width = WIDTH;
    this->height = HEIGHT;
    
    this->numPlayers = DEFAULT_NUM_PLAYERS;
    this->numNodes = DEFAULT_NUM_NODES;
    this->state = DEFAULT_STATE;
    
    this->nullNode = NULL;
    this->nullPlayer = NULL;
    this->nullUnit = NULL;
    this->nullShip = NULL;
        
    selectedNode = nullNode;
    selectedShip = nullShip;
    
    this->rowMax = 0;
    this->rowMin = 0;
    this->colMax = 0;
    this->colMin = 0;
    
    //HELPER STUFF
    srand(SEED);
}

Model * Model::getSelf()
{
    if(!Model::selfPtr)
        Model::selfPtr = new Model();
    return selfPtr;
}

Model::~Model()
{
	delete menu;
    delete playerArray;
    delete map;
    delete nodeArray;
    delete selector;
    delete mgame;
}

Player** Model::setNumPlayers(int numPlayers)
{
    if(!nodeArray) throw new std::string("Allocate Nodes before Players");
    this->numPlayers = numPlayers;
    this->playerArray = new Player*[numPlayers];
    
    for(int i = 0; i < numPlayers; i++)
    {
        playerArray[i] = new Player();
        nodeArray[i]->setType(TYPE_DARK);
        playerArray[i]->conquerNode(nodeArray[i]);
        playerArray[i]->home = nodeArray[i];
        playerArray[i]->addShip(playerArray[i]->home);
    }
    
    return playerArray;
}

Node** Model::setNumNodes(int numNodes)
{
    this->numNodes = numNodes;
    this->nodeArray = new Node*[numNodes];
    for(int i = 0; i < numNodes; i++)
    {
        nodeArray[i] = new Node(random()*NUM_TYPES);
    }
    return nodeArray;
}

Hud * Model::setHud()
{
    hud = new Hud();
    return hud;
}

Map * Model::setMap()
{
    map = new Map(numNodes);
    return map;
}

Selector * Model::setSelector()
{
    this->selector = new Selector();
    return this->selector;
}

Menu * Model::setMenu()
{
    this->menu = new Menu();
    return this->menu;
}

MiniGame * Model::setMiniGame(Node * planet, Ship * attacker, Ship * defender)
{
    this->mgame = new MiniGame(planet, attacker, defender);
    return this->mgame;
}

void Model::enterMiniGame(Node * planet, Ship * attacker, Ship * defender)
{
    setMiniGame(planet, attacker, defender);
    state = MINIGAME;
}

void Model::setCameraParams()
{
    Model::getSelf()->zoom = 4*sqrt(std::max ((float)(rowMax - rowMin), (float)(colMax-colMin))*4.0);
    camCenterX = (colMax + colMin)/2.0;
    camCenterY = (rowMax + rowMin)/2.0;
}



/**
 * HELPER FUNCTIONS
 * Need not do anything specific towards model. Just a universal hub to put useful stuff.
 */

//Generates a value from 0-1. Just makes code cleaner.
float Model::random()
{
    return rand()/(float)RAND_MAX;
}