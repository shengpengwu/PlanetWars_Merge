//
//  Player.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Player.h"

Player::Player()
{
    this->shipArray = new Ship*[Model::getSelf()->numNodes];
    this->numShips = 0;
    this->myNodes = new Node*[Model::getSelf()->numNodes];
    this->nodesOwned = 0;
    this->waterNodesOwned = 0;
    this->earthNodesOwned = 0;
    this->windNodesOwned = 0;
    this->fireNodesOwned = 0;
    this->darkNodesOwned = 0;
    this->darkResources = 0;
}

Player::~Player()
{

}

bool Player::hasNode(Node *node)
{
    for(int i = 0; i < this->nodesOwned; i++)
    {
        if(myNodes[i] == node)
            return true;
    }
    return false;
}

void Player::surrenderNode(Node *node)
{
    bool found;
    
    for(int i = 0; i < this->nodesOwned; i++)
    {
        if(myNodes[i] == node)
            found = true;
        if(found)
            myNodes[i] = myNodes[i+1];
    }
    
    switch(node->type)
    {
        case TYPE_WATER:
            waterNodesOwned--;
            break;
        case TYPE_EARTH:
            earthNodesOwned--;
            break;
        case TYPE_WIND:
            windNodesOwned--;
            break;
        case TYPE_FIRE:
            fireNodesOwned--;
            break;
        case TYPE_DARK:
            darkNodesOwned--;
            break;
    }
    nodesOwned--;
    
    node->owner = Model::getSelf()->nullPlayer;
}

void Player::attackNode(Node *attackNode, Node *defendNode)
{
    
}

void Player::conquerNode(Node *node)
{
    if(!hasNode(node))
    {
        if(node->owner != Model::getSelf()->nullPlayer) 
            node->owner->surrenderNode(node);
        myNodes[nodesOwned+1] = node;
    
    
        switch(node->type)
        {
            case TYPE_WATER:
                waterNodesOwned++;
                break;
            case TYPE_EARTH:
                earthNodesOwned++;
                break;
            case TYPE_WIND:
                windNodesOwned++;
                break;
            case TYPE_FIRE:
                fireNodesOwned++;
                break;
            case TYPE_DARK:
                darkNodesOwned++;
                break;
        }
        nodesOwned++;
        node->owner = this;
    }
}

void Player::endTurn()
{
    refreshShips();
}


bool Player::hasShip(Ship * s)
{
    for(int i = 0; i < numShips; i++)
    {
        if(shipArray[i] == s) return true;
    }
    return false;
}

bool Player::addShip(Node * n)
{
    if(n->ship != Model::getSelf()->nullShip) return false;
    shipArray[numShips] = new Ship(this);
    shipArray[numShips]->loc = n;
    n->ship = shipArray[numShips];
    numShips++;
    return true;
}

void Player::purchaseShip()
{
    if(darkResources < SHIP_COST)
        return;
    if(addShip(home))
        darkResources-=SHIP_COST;
}

void Player::refreshShips()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->tick();
}

void Player::draw()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->drawAtPosition();
}