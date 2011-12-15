#include "Hud.h"


Hud::Hud(void)
{
    pOneNodes = new Node *[NUM_TYPES];
    pTwoNodes = new Node *[NUM_TYPES];
    
    for(int i = 0; i < NUM_TYPES; i++)
    {
        pOneNodes[i] = new Node(i);
        pOneNodes[i]->owner = Model::getSelf()->playerArray[0];
        pOneNodes[i]->display = true;
        pTwoNodes[i] = new Node(i);
        pTwoNodes[i]->owner = Model::getSelf()->playerArray[1];
        pTwoNodes[i]->display = true;
    }
    if(!Hud::compiled) Hud::compileDL();
}


Hud::~Hud(void)
{
}

bool Hud::compiled = false;       //True iff displayList names a valid glDisplayList
GLuint Hud::metaDl;
GLuint Hud::miniDl;
GLuint Hud::mapvDl;

void Hud::compileDL()
{
    if(Hud::compiled) return;
    
    Hud::metaDl = glGenLists(1);
    glNewList(Hud::metaDl, GL_COMPILE);
    
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    glEnd();
    glPopMatrix();
    
    glEndList();   
    
    
    
    
    Hud::miniDl = glGenLists(1);
    glNewList(Hud::miniDl, GL_COMPILE);
    
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    
    glEnd();
    glPopMatrix();
    
    glEndList();   
    
    
    
    
    Hud::mapvDl = glGenLists(1);
    glNewList(Hud::mapvDl, GL_COMPILE);
    float w = (float)Model::getSelf()->width/(float)Model::getSelf()->height;
    float h = (float)Model::getSelf()->height/(float)Model::getSelf()->width;
    glPushMatrix();
    glScalef(w*1.5, h*1.5, 1.0);
    glBegin(GL_QUADS);
    
    //Left
    glVertex3f(-1, -1, -2.0f);
    glVertex3f(-1, 1, -2.0f);
    glVertex3f(-.9, 1, -2.0f);
    glVertex3f(-.9, -1, -2.0f);
    
    //Right
    glVertex3f(.9, -1, -2.0f);
    glVertex3f(.9, 1, -2.0f);
    glVertex3f(1, 1, -2.0f);
    glVertex3f(1, -1, -2.0f);
    
    //Top
    glVertex3f(-1, .9, -2.0f);
    glVertex3f(-1, 1, -2.0f);
    glVertex3f(1, 1, -2.0f);
    glVertex3f(1, .9, -2.0f);
    
    //Bottom
    glVertex3f(-1, -1, -2.0f);
    glVertex3f(-1, -.9, -2.0f);
    glVertex3f(1, -.9, -2.0f);
    glVertex3f(1, -1, -2.0f);

    glEnd();
    glPopMatrix();
    
    glEndList();   
    
    
    
    
    Hud::compiled = true;
}

void Hud::drawMeta()
{
    if(!Hud::compiled) return;

}

void Hud::drawMini()
{
    if(!Hud::compiled) return;


}

void Hud::drawMapv()
{
    if(!Hud::compiled) return;
    setColor(0.5f, 0.5f, 0.5f, 1.0f, 0.1f, 0.5f, 0.7f);
    setGLColor();
    glCallList(mapvDl);
    float dif = -2.0f/((float)NUM_TYPES+2.0f);
    glPushMatrix();
    glTranslated(-1.4, 0.2, 0.0);
    glTranslatef(0.0, 1.0, -2.0);
    glTranslatef(0.0, dif, 0.0);
    for(int i = 0; i < NUM_TYPES; i++)
    {
        glTranslatef(0.0, dif, 0.0);
        glPushMatrix();
        glRotatef(Model::getSelf()->tickCount/10, 0.0, 1.0, 0.0);
        glRotatef(80, 1.0f, 0.0f, 0.0f);
        glScalef(0.1,0.1,0.1);
        pOneNodes[i]->draw();
        glPopMatrix();
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1.4, 0.2, 0.0);
    glTranslatef(0.0, 1.0, -2.0);
    glTranslatef(0.0, dif, 0.0);
    for(int i = 0; i < NUM_TYPES; i++)
    {
        glTranslatef(0.0, dif, 0.0);
        glPushMatrix();
        glRotatef(Model::getSelf()->tickCount/10, 0.0, 1.0, 0.0);
        glRotatef(80, 1.0f, 0.0f, 0.0f);
        glScalef(0.1,0.1,0.1);
        pTwoNodes[i]->draw();
        glPopMatrix();
    }
    glPopMatrix();
    
}