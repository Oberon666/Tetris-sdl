// CApp_OnLoop.cpp
#include "CApp.h"

//--------------------------------------------
void CApp::OnLoop(){
	switch (movingFigure.direction){
		case MovingFigure::left:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				Grid::instance().leftFigure();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					Grid::instance().leftFigure();
				}
			break;
		}
		case MovingFigure::right:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				Grid::instance().rightFigure();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					Grid::instance().rightFigure();
				}
			break;
		}
	}
}
//--------------------------------------------
