// CSurface.h
#ifndef CSURFACE_H
#define CSURFACE_H

#include <SDL/SDL.h>

//--------------------------------------------
class CSurface{
public:
	CSurface();
	static SDL_Surface* OnLoad(const char *File);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Scr, int X, int Y);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Scr,
					   int X, int Y, int X2, int Y2, int W, int H);
	static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
};
//--------------------------------------------
#endif // CSURFACE_H
