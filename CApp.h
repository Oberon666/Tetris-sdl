// CApp.h
#ifndef CAPP_H
#define CAPP_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "CSurface.h"
#include "CEvent.h"
#include "Tetris.h"
#include "CApp_Timer.h"

//--------------------------------------------
class CApp: public CEvent{
public:
	CApp();
	~CApp();
	int OnExecute();

private:
	bool Running;
	Timer fps, logic, speedLevelT;

	//for long press
	struct MovingFigure{
		Timer LongPressTimer;
		enum Direction{
			left,
			right,
			constant
		} direction;
		MovingFigure();
	} movingFigure;

	unsigned char FramesPerSecond;
	long int frame;
	int delayLogic;
	int buffer;
	bool pauseGame;
	unsigned char speedLevel;

	SDL_Surface* SurfDisplay;
	SDL_Surface* SurfNone;
	SDL_Surface* SurfDown;
	SDL_Surface* SurfFixed;
	SDL_Surface* SurfWhite;

	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnCleanup();
	void parsingLogic(int key);

	//sound
	Mix_Chunk* mixRow;
	Mix_Chunk* mixDown;
	Mix_Music* mixMusix;

	//шрифты
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Surface* message;
	bool textRender;

	//переопределенные события
	void OnExit();
	void OnLButtonDown(int mX, int mY);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};
//--------------------------------------------
#endif // CAPP_H
