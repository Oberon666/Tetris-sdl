// CSurface.cpp

#include "myHeader.h"
#include "CSurface.h"
#include <SDL/SDL_image.h>

CSurface::CSurface(){
}
//--------------------------------------------
// load texture in surface
SDL_Surface* CSurface::OnLoad(const char* File){
	SDL_Surface* Surf_Temp = 0;
	SDL_Surface* Surf_Return = 0;

	//    if ((Surf_Temp = SDL_LoadBMP(File)) == 0)
	if ((Surf_Temp = IMG_Load(File)) == 0){
		Vet::myError( "error to CSurface::OnLoad", SDL_GetError());
		return (0);
	}

	Surf_Return = SDL_DisplayFormat(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);

	return (Surf_Return);
}
//--------------------------------------------
// draw Surf_Scr on Surf_Dest
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Scr, int X, int Y){
	if (Surf_Dest == 0 || Surf_Scr == 0)
		return (false);

	SDL_Rect DestR;
	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Scr, 0, Surf_Dest, &DestR);

	return (true);
}
//--------------------------------------------
// draw area Surf_Scr on Surf_Dest
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Scr,
					  int X, int Y, int X2, int Y2, int W, int H){
	if (Surf_Dest == 0 || Surf_Scr == 0)
		return (false);

	SDL_Rect DestR;
	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;
	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Scr, &SrcR, Surf_Dest, &DestR);

	return (true);
}
//--------------------------------------------
// sets the transparent
bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B){
	if (Surf_Dest == 0)
		return (false);

	SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL,
					SDL_MapRGB(Surf_Dest->format, R, G, B));
	return (true);
}
//--------------------------------------------
