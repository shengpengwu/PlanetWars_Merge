
#ifdef TARGET_OS_MAC
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#endif

#ifdef __linux__
  // Linux Includes Here
  #error Can't be compiled on Linux yet
#endif

#ifdef _WIN32 || _WIN64
#include "GL\freeglut.h"
    #include <GL\GL.h>
#endif

#ifndef H_TEXTPRINT
#define H_TEXTPRINT

#include "Model.h"
#include "DrawableGeometry.h"

class TextPrint
{
public:
	TextPrint(void);
	~TextPrint(void);
	
/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18

*/
	static void bitText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	static void hudText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	static void strokePrint(int x, int y, int z, float r, float g, float b, char *string);
};

#endif