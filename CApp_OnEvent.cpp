// CApp_Event.cpp
#include "CApp.h"

//--------------------------------------------
void CApp::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}
//--------------------------------------------
void CApp::OnExit(){
	Running = false;
}
//--------------------------------------------
void CApp::OnLButtonDown(int mX, int mY){
	return;
}
//--------------------------------------------
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch (sym){
		case SDLK_ESCAPE:{
			Running = false;
			break;
		}
		case SDLK_UP:{
			if (!pauseGame){
				Grid::instance().turnFigure();
			}
			break;
		}
		case SDLK_DOWN:{
			buffer = delayLogic;
			delayLogic =50;
			break;
		}
		case SDLK_LEFT:{
			if (!pauseGame){
				movingFigure.direction = static_cast<MovingFigure::Direction>(0);
			}
			break;
		}
		case SDLK_RIGHT:{
			if (!pauseGame){
				movingFigure.direction = static_cast<MovingFigure::Direction>(1);
			}
			break;
		}
		case SDLK_RETURN:{
			pauseGame = false;
			logic.start();
			speedLevelT.start();
		}
		default: break;
	}
}
//--------------------------------------------
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch (sym){
		case SDLK_UP:{
			break;
		}
		case SDLK_DOWN:{
			delayLogic = buffer;
			buffer = 0;
			break;
		}
		case SDLK_LEFT:{
			if (!pauseGame){
				movingFigure.direction = MovingFigure::constant;
				movingFigure.LongPressTimer.stop();
			}
			break;
		}
		case SDLK_RIGHT:{
			if (!pauseGame){
				movingFigure.direction = MovingFigure::constant;
				movingFigure.LongPressTimer.stop();
			}
			break;
		}
		default: break;
	}
}
//--------------------------------------------
