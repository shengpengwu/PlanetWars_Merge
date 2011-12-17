

#include "TextPrint.h"

TextPrint::TextPrint(void)
{
}


TextPrint::~TextPrint(void)
{
}




/*
 * Prints characters from GLUT in the 3d world which will always face the screen.
 *       Do not push or pop matrices before this!
 */


void TextPrint::bitText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
	glColor3f( r, g, b );
	glRasterPos3f(x, y, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

// Standalone function that will automatically place words in a HUD.
void TextPrint::hudText(int x, int y, int z, 
	float r, float g, float b, void * font, char *string)
{
	glColor3f( r, g, b );
	glRasterPos3f(x, y, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}

}

/*	
Stroke doesn't work right now.

Stroke fonts:
GLUT_STROKE_ROMAN
GLUT_STROKE_MONO_ROMAN
*/

void TextPrint::strokePrint(int x, int y, int z, 
	float r, float g, float b, char *string)
{
	char *p;
    
    glPushMatrix();
    glTranslatef(x, y, z);
    for (p = string; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();

}