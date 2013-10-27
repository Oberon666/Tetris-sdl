//Tetris.cpp
#include "myHeader.h"
#include "Tetris.h"
#include <cassert>

// Settings
const std::string Settings::pathNone = "pictures_40/None.png";
const std::string Settings::pathDown = "pictures_40/Down.png";
const std::string Settings::pathFixed = "pictures_40/Fixed.png";
const std::string Settings::pathWhite = "pictures_40/White.png";


void cleaner_sp(Figure* object){
	Vet::myError("опа!\n");
}

//Grid===========================================
Grid::Grid()://activeFigure(new Figure), nextFigure(new Figure(static_cast<figure_Type>(0))),
	activeFigure( objectPool.creatObject()),
	nextFigure(objectPool.creatObject()), turneFigure(0),
	activeFigureX(3), activeFigureY(0), nextFigureId(1), points(0),
	renderGrid(true), renderMenu(true), renderNextFigure(true){

//	activeFigure.reset(objectPool.creatObject());
//	nextFigure.reset(objectPool.creatObject());

	activeFigureY = activeFigure->getBorder().uY - 2;// поправка если есть пустоты
	figureInGrid(activeFigure);
}
//--------------------------------------------
Grid::~Grid(){
}
//--------------------------------------------
// grid filling grid_None
void Grid::resetGrid(){
	for (int j = 0; j < Settings::gridActiveHeight; ++j)
		for (int i = 0; i < Settings::gridActiveWidth; ++i)
			gridArray[j][i] = board_None;
	renderGrid = true;
}
//--------------------------------------------
// singleton for Grid
Grid& Grid::instance(){
	static Grid inst_Grid;
	return (inst_Grid);
}
//--------------------------------------------
board_Type Grid::getGridArray(unsigned int j,  unsigned int i) const{
	assert(j >= 0 && j < Settings::gridActiveHeight);
	assert(i >= 0 && i < Settings::gridActiveWidth);
	return (gridArray[j][i]);
}
//--------------------------------------------
// turn active figure
void Grid::turnFigure(){
	turneFigure = objectPool.creatObject();
	if ( !activeFigure->cloneTurned(turneFigure) ){
		objectPool.deleteObject(turneFigure);
		return;
	}
	if ( verification(turneFigure, activeFigureY , activeFigureX) ){
		figureOutGrid(activeFigure);
		objectPool.deleteObject(activeFigure);
		activeFigure = turneFigure;
		figureInGrid(activeFigure);
		renderGrid = true;
	}
	else
		if ( verification(turneFigure, activeFigureY , activeFigureX +1) ){
			figureOutGrid(activeFigure);
			++activeFigureX;
			objectPool.deleteObject(activeFigure);
			activeFigure = turneFigure;
			figureInGrid(activeFigure);
			renderGrid = true;
		}
		else
			if ( verification(turneFigure, activeFigureY , activeFigureX -1) ){
				figureOutGrid(activeFigure);
				--activeFigureX;
				objectPool.deleteObject(activeFigure);
				activeFigure = turneFigure;
				figureInGrid(activeFigure);
				renderGrid = true;
			}
			else
				if ( verification(turneFigure, activeFigureY +1 , activeFigureX) ){
					figureOutGrid(activeFigure);
					++activeFigureY;
					objectPool.deleteObject(activeFigure);
					activeFigure = turneFigure;
					figureInGrid(activeFigure);
					renderGrid = true;
				}
				else
					if ( verification(turneFigure, activeFigureY , activeFigureX +2) ){
						figureOutGrid(activeFigure);
						activeFigureX+=2;
						objectPool.deleteObject(activeFigure);
						activeFigure = turneFigure;
						figureInGrid(activeFigure);
						renderGrid = true;
					}
					else
						if ( verification(turneFigure, activeFigureY , activeFigureX -2) ){
							figureOutGrid(activeFigure);
							activeFigureX-=2;
							objectPool.deleteObject(activeFigure);
							activeFigure = turneFigure;
							figureInGrid(activeFigure);
							renderGrid = true;
						}
						else
							if ( verification(turneFigure, activeFigureY +2 , activeFigureX) ){
								figureOutGrid(activeFigure);
								activeFigureY+=2;
								objectPool.deleteObject(activeFigure);
								activeFigure = turneFigure;
								figureInGrid(activeFigure);
								renderGrid = true;
							}
}
//--------------------------------------------
// acceleration down for active figure
void Grid::downFigure(){
	if (verification(activeFigure, activeFigureY +1, activeFigureX)){
		figureOutGrid(activeFigure);
		++activeFigureY;
		figureInGrid(activeFigure);
		renderGrid = true;
	}
}
//--------------------------------------------
// moving active figure to left
void Grid::leftFigure(){
	if (verification(activeFigure, activeFigureY, activeFigureX - 1)){
		figureOutGrid(activeFigure);
		--activeFigureX;
		figureInGrid(activeFigure);
		renderGrid = true;
	}
}
//--------------------------------------------
// moving active figure to right
void Grid::rightFigure(){
	if (verification(activeFigure, activeFigureY, activeFigureX + 1)){
		figureOutGrid(activeFigure);
		++activeFigureX;
		figureInGrid(activeFigure);
		renderGrid = true;
	}
}
//--------------------------------------------
// mapping figure to gridArray as grid_Down
void Grid::figureInGrid(const Figure* figure){
	assert(figure != 0);
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				gridArray[j + activeFigureY][i + activeFigureX] = board_Down;
	renderGrid = true;
}
//--------------------------------------------
// mapping figure to gridArray as grid_None
void Grid::figureOutGrid(const Figure *figure){
	assert(figure != 0);
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				gridArray[j + activeFigureY][i + activeFigureX] = board_None;
	renderGrid = true;
}
//--------------------------------------------
// mapping figure to gridArray as grid_Fixed
void Grid::figureFixed(const Figure *figure){
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				gridArray[j + activeFigureY][i + activeFigureX] = board_Fixed;
	renderGrid = true;
}
//--------------------------------------------
// check the display in an array of shapes
bool Grid::verification(const Figure *figure,
						short int newJ, short int newI) const{
	assert(figure != 0);
	//если попали за границы поля
	if (newI+2-figure->getBorder().lX < 0 || newI+2+figure->getBorder().rX > Settings::gridActiveWidth-1)
		return (false);
	if (newJ+2-figure->getBorder().uY  < 0 || newJ+2+figure->getBorder().dY > Settings::gridActiveHeight-1)
		return (false);

	//если натолкнулись на припятствие
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				if (gridArray[j + newJ][i + newI] != board_None &&
						gridArray[j + newJ][i + newI] != board_Down)
					return (false);
	return (true);
}
//--------------------------------------------
// return true if firure can not dawn (check "activeFigureY +1")
bool Grid::notDownsFigure(const Figure *figure) const{
	assert(figure != 0);
	if (!verification(figure, activeFigureY +1, activeFigureX))
		return (true);
	return (false);
}
//--------------------------------------------
// in process... переделать костыли
// 1 - звук падения, 2 - звук сброса, 3 - конец игры
unsigned char Grid::logic(){
	if (notDownsFigure(activeFigure))// если не можем двигать, двигаем
	{
		unsigned char rezult(1);
		figureFixed(activeFigure);//зафиксировали
		if (lowerRow())//сбросилось?
			rezult = 2;
		objectPool.deleteObject(activeFigure);
		activeFigure = nextFigure;//вытащили следующую фигуру
		activeFigureY = activeFigure->getBorder().uY - 2;//стандартая корректировка от пустот
		activeFigureX = 3;
		nextFigure = objectPool.creatObject();// обновили новую фигуру
		renderNextFigure = true;
		++nextFigureId; // счетчик новой фигуры
		if (notDownsFigure(activeFigure)){//если она не лезит в стакан, то конец
			gameOver();
			figureInGrid(activeFigure);
			return (3);
		}
		figureInGrid(activeFigure);//выкатили новую фигуру на поле
		return(rezult);
	}
	else{
		downFigure();
		return (0);
	}
}
//--------------------------------------------
// end game
void Grid::gameOver(){
	// проверить что подчистил все сотояния
	points = 0;
	resetGrid();
}
//--------------------------------------------
bool Grid::getNextFigure(int j, int i) const{
	assert(j >= 0 && j < Figure::sizeFigure);
	assert(i >= 0 && i < Figure::sizeFigure);
	return (nextFigure->getArrayFigure(j, i));
}
//--------------------------------------------
// index "next figure"
unsigned long int Grid::getNextFigureId() const{
	return (nextFigureId);
}
//--------------------------------------------
// Search full rows, reset it and shift
bool Grid::lowerRow(){
	bool check, rezult(false);
	for (int j = 0; j < Settings::gridActiveHeight; ++j){
		check = true;
		for (int i = 0; i < Settings::gridActiveWidth; ++i){
			if (gridArray[j][i] != board_Fixed)
				check = false;
		}
		if (check){
			rezult = true;
			for (int i = Settings::gridActiveWidth-1; i >= 0; --i)
				gridArray[j][i] = board_None;
			RowsDown(j);
			++points;
		}
	}
	return (rezult);
}
//--------------------------------------------
//down rows [y-1..0] to [y..1]
void Grid::RowsDown(int y){
	for (int j = y-1; j >= 0; --j){
		for (int i = Settings::gridActiveWidth-1; i >= 0; --i)
			gridArray[j+1][i] = gridArray[j][i];
	}
}
//--------------------------------------------
unsigned int Grid::getPoints() const{
	return (points);
}
//--------------------------------------------
