// CApp_OnLoop.cpp
#include "CApp.h"

//--------------------------------------------
void CApp::OnLoop(){
	switch (movingFigure.direction){
		case MovingFigure::left:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				Board::instance().leftShape();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					Board::instance().leftShape();
				}
			break;
		}
		case MovingFigure::right:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				Board::instance().rightShape();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					Board::instance().rightShape();
				}
			break;
		}
	}
}
//--------------------------------------------
