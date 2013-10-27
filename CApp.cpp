// CApp.cpp
//  Каркас для работы с SDL. Oberon
#include "myHeader.h"
#include <iostream>
#include <csignal>
#include "CApp.h"

//--------------------------------------------
CApp::CApp(): Running(true), SurfDisplay(0), SurfNone(0), SurfDown(0),
	SurfFixed(0), SurfWhite(0), delayLogic(1000), FramesPerSecond(50),
	frame(0), speedLevel(1), font(0), textRender(true),
	pauseGame(true), buffer(0), mixRow(0), mixDown(0), mixMusix(0), message(0)
{
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 150;
}
//--------------------------------------------
CApp::MovingFigure::MovingFigure(): direction(constant) {
}
//--------------------------------------------
//--------------------------------------------
CApp::~CApp() {
	OnCleanup();
}
//--------------------------------------------
int CApp::OnExecute() {
	try{
		signal(SIGFPE, Vet::myTer);
		if(OnInit() == false) {
			return -1;
		}

//		int i = 0;
//		i= i/i;

		SDL_Event Event;
		Mix_PlayMusic( mixMusix, -1 );
		unsigned char rezultLogic(0);

		while(Running){
			if (!pauseGame)
				fps.start();

			while(SDL_PollEvent(&Event)) {
				OnEvent(&Event);
			}

			OnLoop();
			//throw(std::bad_alloc() );

			if (!pauseGame) {
				if (speedLevelT.getTick() > 60000) {
					if (delayLogic >75){
						if (buffer != 0)
							buffer -= 75;
						else
							delayLogic -= 75;
						++speedLevel;
						speedLevelT.start();
						std::cout<<int(speedLevel) <<"\t" <<delayLogic <<std::endl;
					}
				}

				if (logic.getTick() > delayLogic) {
					logic.start();
					rezultLogic = Board::instance().logic();
					parsingLogic(rezultLogic);
					rezultLogic = 0;
				}
			}

			OnRender();

						if (fps.getTick() > 40)
						std::cout<<(1000/FramesPerSecond) -fps.getTick()<<std::endl;
			if ( fps.getTick() < (1000/FramesPerSecond) ){
				SDL_Delay( (1000/FramesPerSecond) - fps.getTick() );
			}
		}

	}catch(...) {
		Vet::myError("indefinite exception in CApp::OnExecute().");
	}

	return 0;
}
//--------------------------------------------
void CApp::parsingLogic(int key) {
	switch (key) {
		case 1:
			Mix_PlayChannel( -1, mixDown, 0 );
			break;
		case 2:
			Mix_PlayChannel( -1, mixRow, 0 );
			std::cout<<Board::instance().getPoints() <<std::endl;
			break;
		case 3:
			pauseGame = true;
			if (buffer != 0)
				buffer = 1000;
			else
				delayLogic = 1000;
			movingFigure.direction = MovingFigure::constant;
			movingFigure.LongPressTimer.stop();
;
			speedLevel = 1;
			logic.stop();
			speedLevelT.stop();
			fps.stop();
			break;
	}
}
//--------------------------------------------
int main(int argc, char* argv[]) {
	CApp myApp;

	return myApp.OnExecute();
}
//--------------------------------------------
