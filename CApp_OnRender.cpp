// CApp_OnRender.cpp
#include "myHeader.h"
#include "CApp.h"

//--------------------------------------------
void CApp::OnRender(){
	//render fon for menu
	if (boardI.renderMenu){
		boardI.renderMenu = false;
		for (int j = 0; j < Settings::boardActiveHeight; ++j)
			for (int i = 0; i < Settings::boardMenuWidth; ++i)
				CSurface::OnDraw(SurfDisplay, SurfWhite, (i + Settings::boardActiveWidth)*Settings::sizePrimitive, j*Settings::sizePrimitive);

		message = TTF_RenderText_Solid(
					font,
					"Key: Enter, <-, ^ , ->",
					textColor);
		CSurface::OnDraw(SurfDisplay, message,
						 (Settings::boardActiveWidth)*Settings::sizePrimitive + 40,
						 Settings::sizePrimitive * 6);
	}

	//render game field
	if (boardI.renderBoard){
		boardI.renderBoard = false;
		for (int j = 0; j < Settings::boardActiveHeight; ++j){
			for (int i = 0; i < Settings::boardActiveWidth; ++i){
				if (boardI.getBoardArray(j, i) == board_Down)
					CSurface::OnDraw(SurfDisplay, SurfDown, i*Settings::sizePrimitive, j*Settings::sizePrimitive);

				if (boardI.getBoardArray(j, i) == board_Fixed)
					CSurface::OnDraw(SurfDisplay, SurfFixed, i*Settings::sizePrimitive, j*Settings::sizePrimitive);

				if (boardI.getBoardArray(j, i) == board_None)
					CSurface::OnDraw(SurfDisplay, SurfNone, i*Settings::sizePrimitive, j*Settings::sizePrimitive);
			}
		}
	}

	//render next figure
	if (boardI.renderNextShape){
		boardI.renderNextShape = false;
		for (int j = 0; j < Shape::sizeShape; ++j)
			for (int i = 0; i < Shape::sizeShape; ++i)
				if (boardI.getNextShape(j, i) != 0)
					CSurface::OnDraw(SurfDisplay, SurfDown,
									 i*Settings::sizePrimitive+(Settings::boardActiveWidth+1)*Settings::sizePrimitive,
									 j*Settings::sizePrimitive+Settings::sizePrimitive);
				else
					CSurface::OnDraw(SurfDisplay, SurfWhite,
									 i*Settings::sizePrimitive+(Settings::boardActiveWidth+1)*Settings::sizePrimitive,
									 j*Settings::sizePrimitive+Settings::sizePrimitive);
	}

	if ( SDL_Flip(SurfDisplay) == -1 ){
		Vet::myError( "error to SDL_Flip", SDL_GetError());
	}
}
//--------------------------------------------
