#include "MiniGame.h"

MiniGame::MiniGame(Node * planet, Ship * attackerShip, Ship * defenderShip)
{
    node = planet;
    attacker = attackerShip;
    defender = defenderShip;
    
    lanes = new Lane*[NUM_LANES];
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i] = new Lane();
    }
    selectedLane = 0;
    lanes[selectedLane]->setSelected(true);
}

void MiniGame::changeLane(int direction)
{
    if(direction == LEFT && selectedLane != 0)
        selectLane(selectedLane-1);
    else if(direction == RIGHT && selectedLane != 4)
        selectLane(selectedLane+1);
}

void MiniGame::selectLane(int lane)
{
    lanes[selectedLane]->setSelected(false);
    selectedLane = lane;
    lanes[selectedLane]->setSelected(true);
}

void MiniGame::deployUnit(Ship * s, int type) {
    Unit * u = s->deployUnit(type);
    if(u != Model::getSelf()->nullUnit)
    {
        lanes[selectedLane]->deployUnit(u, (s == attacker));
    }
}

void MiniGame::update() {
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i]->tick();
    }
}


void MiniGame::drawGame() {
    //Draw Lanes
    for(int i = 0; i < NUM_LANES; i++)
    {
        glPushMatrix();
        glTranslated((double)((LANE_WIDTH*i)-(LANE_WIDTH*(int)(NUM_LANES/2))), 0.0, 0.0);
        lanes[i]->draw();
        glPopMatrix();
    }

	glBegin(GL_QUADS);
    glVertex3f(-10, -1, 10);
	glVertex3f(10, -1, 10);
	glVertex3f(10, -1, 10);
	glVertex3f(-10, -1, 10);
	glEnd();

	glBegin(GL_QUADS);
    glVertex3f(-10, -1, 60);
	glVertex3f(10, -1, 60);
	glVertex3f(10, -1, 70);
	glVertex3f(-10, -1, 70);
	glEnd();

}




