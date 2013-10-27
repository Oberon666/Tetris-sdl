// CApp_OnLoop.cpp
#include "CApp.h"

//--------------------------------------------
void CApp::OnLoop(){
	switch (movingFigure.direction){
		case MovingFigure::left:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				boardI.leftShape();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					boardI.leftShape();
				}
			break;
		}
		case MovingFigure::right:{
			if (!movingFigure.LongPressTimer.isStarted()){
				movingFigure.LongPressTimer.start();
				boardI.rightShape();
			}
			else
				if (movingFigure.LongPressTimer.getTick() > 200){
					boardI.rightShape();
				}
			break;
		}
	}
}
//--------------------------------------------
