

#ifndef H_TEXTPRINT
#define H_TEXTPRINT

// I'm not sure if I will need to include this later.
#include "Model.h"

class TextPrint
{
public:
	TextPrint(void);
	~TextPrint(void);
	static void bitText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	static void hudText(int x, int y, int z, float r, float g, float b, void * font, char *string);
	static void strokePrint(int x, int y, int z, float r, float g, float b, char *string);
private:
};

#endif