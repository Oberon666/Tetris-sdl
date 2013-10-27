// CApp_OnLoop.cpp
#include "CApp.h"

//--------------------------------------------
void CApp::OnLoop(){
	switch (movingFigure.direction){
		case MovingFigure::left:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				Board::instance().leftFigure();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					Board::instance().leftFigure();
				}
			break;
		}
		case MovingFigure::right:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				Board::instance().rightFigure();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					Board::instance().rightFigure();
				}
			break;
		}
	}
}
//--------------------------------------------
