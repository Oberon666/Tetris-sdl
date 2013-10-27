// CApp_OnRender.cpp
#include "myHeader.h"
#include "CApp.h"

//--------------------------------------------
void CApp::OnRender(){
	//render fon for menu
	if (Grid::instance().renderMenu){
		Grid::instance().renderMenu = false;
		for (int j = 0; j < Settings::gridActiveHeight; ++j)
			for (int i = 0; i < Settings::gridMenuWidth; ++i)
				CSurface::OnDraw(SurfDisplay, SurfWhite, (i + Settings::gridActiveWidth)*Settings::sizePrimitive, j*Settings::sizePrimitive);

		message = TTF_RenderText_Solid(
					font,
					"Key: Enter, <-, ^ , ->",
					textColor);
		CSurface::OnDraw(SurfDisplay, message,
						 (Settings::gridActiveWidth)*Settings::sizePrimitive + 40,
						 Settings::sizePrimitive * 6);
	}

	//render game field
	if (Grid::instance().renderGrid){
		Grid::instance().renderGrid = false;
		for (int j = 0; j < Settings::gridActiveHeight; ++j){
			for (int i = 0; i < Settings::gridActiveWidth; ++i){
				if (Grid::instance().getGridArray(j, i) == grid_Down)
					CSurface::OnDraw(SurfDisplay, SurfDown, i*Settings::sizePrimitive, j*Settings::sizePrimitive);

				if (Grid::instance().getGridArray(j, i) == grid_Fixed)
					CSurface::OnDraw(SurfDisplay, SurfFixed, i*Settings::sizePrimitive, j*Settings::sizePrimitive);

				if (Grid::instance().getGridArray(j, i) == grid_None)
					CSurface::OnDraw(SurfDisplay, SurfNone, i*Settings::sizePrimitive, j*Settings::sizePrimitive);
			}
		}
	}

	//render next figure
	if (Grid::instance().renderNextFigure){
		Grid::instance().renderNextFigure = false;
		for (int j = 0; j < Figure::sizeFigure; ++j)
			for (int i = 0; i < Figure::sizeFigure; ++i)
				if (Grid::instance().getNextFigure(j, i) != 0)
					CSurface::OnDraw(SurfDisplay, SurfDown,
									 i*Settings::sizePrimitive+(Settings::gridActiveWidth+1)*Settings::sizePrimitive,
									 j*Settings::sizePrimitive+Settings::sizePrimitive);
				else
					CSurface::OnDraw(SurfDisplay, SurfWhite,
									 i*Settings::sizePrimitive+(Settings::gridActiveWidth+1)*Settings::sizePrimitive,
									 j*Settings::sizePrimitive+Settings::sizePrimitive);
	}

	if ( SDL_Flip(SurfDisplay) == -1 ){
		Vet::myError( "error to SDL_Flip", SDL_GetError());
	}
}
//--------------------------------------------
