// CApp_OnInit.cpp
#include "myHeader.h"
#include "CApp.h"

//--------------------------------------------
bool CApp::OnInit(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		Vet::myError( "error to SDL_Init", SDL_GetError());
		return (false);
	}

	if (TTF_Init() == -1){
		Vet::myError( "error to TTF_Init", SDL_GetError());
		return (false);
	}

	if ((SurfDisplay = SDL_SetVideoMode(
			 Settings::boardActiveWidth * Settings::sizePrimitive +
			 Settings::boardMenuWidth * Settings::sizePrimitive,
			 Settings::boardActiveHeight * Settings::sizePrimitive, 24,
			 SDL_HWSURFACE | SDL_DOUBLEBUF)) == 0){//SDL_RESIZABLE
		Vet::myError( "error to SDL_SetVideoMode", SDL_GetError());
		return (false);
	}

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1){
		Vet::myError( "error to Mix_OpenAudio", SDL_GetError());
		return (false);
	}

	if ( (mixMusix = Mix_LoadMUS( "sound/music.wav" )) == 0 ){
		Vet::myError( "error to Mix_LoadMUS", SDL_GetError());
		return (false);
	}
	if ( (mixRow = Mix_LoadWAV( "sound/rows.wav" )) == 0 ){
		Vet::myError( "error to Mix_LoadWAV", SDL_GetError());
		return (false);
	}

	if ( (mixDown = Mix_LoadWAV( "sound/down.wav" )) == 0 ){
		Vet::myError( "error to Mix_LoadWAV", SDL_GetError());
		return (false);
	}

	if ( (font = TTF_OpenFont( "font/GOST_type_A.ttf", 25 )) == 0 ){
		Vet::myError( "error to TTF_OpenFont", SDL_GetError());
		return (false);
	}

	if ((SurfNone = CSurface::OnLoad( Settings::pathNone.c_str() )) ==0)
		return (false);
	if ((SurfDown = CSurface::OnLoad(Settings::pathDown.c_str() )) ==0)
		return (false);
	if ((SurfFixed = CSurface::OnLoad(Settings::pathFixed.c_str() )) ==0)
		return (false);
	if ((SurfWhite = CSurface::OnLoad(Settings::pathWhite.c_str() )) ==0)
		return (false);

	SDL_WM_SetCaption( "Tetris", NULL );

	return true;
}
//--------------------------------------------
