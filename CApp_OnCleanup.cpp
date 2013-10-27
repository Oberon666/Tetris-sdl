// CApp_OnCleanup.cpp
#include "CApp.h"
#include <iostream>

//--------------------------------------------
void CApp::OnCleanup(){
	SDL_FreeSurface(SurfWhite);
	SDL_FreeSurface(SurfFixed);
	SDL_FreeSurface(SurfDown);
	SDL_FreeSurface(SurfNone);
	SDL_FreeSurface(SurfDisplay);

	Mix_FreeChunk(mixRow);
	Mix_FreeChunk(mixDown);
	Mix_FreeMusic(mixMusix);

	TTF_CloseFont( font );
	SDL_FreeSurface(message);

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}
//--------------------------------------------
