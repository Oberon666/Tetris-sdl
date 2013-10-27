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
Board::Board()://activeFigure(new Figure), nextFigure(new Figure(static_cast<figure_Type>(0))),
	activeFigure( objectPool.creatObject()),
	nextFigure(objectPool.creatObject()), turneFigure(0),
	activeFigureX(3), activeFigureY(0), nextFigureId(1), points(0),
	renderBoard(true), renderMenu(true), renderNextFigure(true){

//	activeFigure.reset(objectPool.creatObject());
//	nextFigure.reset(objectPool.creatObject());

	activeFigureY = activeFigure->getBorder().uY - 2;// поправка если есть пустоты
	figureInBoard(activeFigure);
}
//--------------------------------------------
Board::~Board(){
}
//--------------------------------------------
// grid filling grid_None
void Board::resetBoard(){
	for (int j = 0; j < Settings::boardActiveHeight; ++j)
		for (int i = 0; i < Settings::boardActiveWidth; ++i)
			boardArray[j][i] = board_None;
	renderBoard = true;
}
//--------------------------------------------
// singleton for Grid
Board& Board::instance(){
	static Board inst_Grid;
	return (inst_Grid);
}
//--------------------------------------------
board_Type Board::getBoardArray(unsigned int j,  unsigned int i) const{
	assert(j >= 0 && j < Settings::boardActiveHeight);
	assert(i >= 0 && i < Settings::boardActiveWidth);
	return (boardArray[j][i]);
}
//--------------------------------------------
// turn active figure
void Board::turnFigure(){
	turneFigure = objectPool.creatObject();
	if ( !activeFigure->cloneTurned(turneFigure) ){
		objectPool.deleteObject(turneFigure);
		return;
	}
	if ( verification(turneFigure, activeFigureY , activeFigureX) ){
		figureOutBoard(activeFigure);
		objectPool.deleteObject(activeFigure);
		activeFigure = turneFigure;
		figureInBoard(activeFigure);
		renderBoard = true;
	}
	else
		if ( verification(turneFigure, activeFigureY , activeFigureX +1) ){
			figureOutBoard(activeFigure);
			++activeFigureX;
			objectPool.deleteObject(activeFigure);
			activeFigure = turneFigure;
			figureInBoard(activeFigure);
			renderBoard = true;
		}
		else
			if ( verification(turneFigure, activeFigureY , activeFigureX -1) ){
				figureOutBoard(activeFigure);
				--activeFigureX;
				objectPool.deleteObject(activeFigure);
				activeFigure = turneFigure;
				figureInBoard(activeFigure);
				renderBoard = true;
			}
			else
				if ( verification(turneFigure, activeFigureY +1 , activeFigureX) ){
					figureOutBoard(activeFigure);
					++activeFigureY;
					objectPool.deleteObject(activeFigure);
					activeFigure = turneFigure;
					figureInBoard(activeFigure);
					renderBoard = true;
				}
				else
					if ( verification(turneFigure, activeFigureY , activeFigureX +2) ){
						figureOutBoard(activeFigure);
						activeFigureX+=2;
						objectPool.deleteObject(activeFigure);
						activeFigure = turneFigure;
						figureInBoard(activeFigure);
						renderBoard = true;
					}
					else
						if ( verification(turneFigure, activeFigureY , activeFigureX -2) ){
							figureOutBoard(activeFigure);
							activeFigureX-=2;
							objectPool.deleteObject(activeFigure);
							activeFigure = turneFigure;
							figureInBoard(activeFigure);
							renderBoard = true;
						}
						else
							if ( verification(turneFigure, activeFigureY +2 , activeFigureX) ){
								figureOutBoard(activeFigure);
								activeFigureY+=2;
								objectPool.deleteObject(activeFigure);
								activeFigure = turneFigure;
								figureInBoard(activeFigure);
								renderBoard = true;
							}
}
//--------------------------------------------
// acceleration down for active figure
void Board::downFigure(){
	if (verification(activeFigure, activeFigureY +1, activeFigureX)){
		figureOutBoard(activeFigure);
		++activeFigureY;
		figureInBoard(activeFigure);
		renderBoard = true;
	}
}
//--------------------------------------------
// moving active figure to left
void Board::leftFigure(){
	if (verification(activeFigure, activeFigureY, activeFigureX - 1)){
		figureOutBoard(activeFigure);
		--activeFigureX;
		figureInBoard(activeFigure);
		renderBoard = true;
	}
}
//--------------------------------------------
// moving active figure to right
void Board::rightFigure(){
	if (verification(activeFigure, activeFigureY, activeFigureX + 1)){
		figureOutBoard(activeFigure);
		++activeFigureX;
		figureInBoard(activeFigure);
		renderBoard = true;
	}
}
//--------------------------------------------
// mapping figure to gridArray as grid_Down
void Board::figureInBoard(const Figure* figure){
	assert(figure != 0);
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				boardArray[j + activeFigureY][i + activeFigureX] = board_Down;
	renderBoard = true;
}
//--------------------------------------------
// mapping figure to gridArray as grid_None
void Board::figureOutBoard(const Figure *figure){
	assert(figure != 0);
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				boardArray[j + activeFigureY][i + activeFigureX] = board_None;
	renderBoard = true;
}
//--------------------------------------------
// mapping figure to gridArray as grid_Fixed
void Board::figureFixed(const Figure *figure){
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				boardArray[j + activeFigureY][i + activeFigureX] = board_Fixed;
	renderBoard = true;
}
//--------------------------------------------
// check the display in an array of shapes
bool Board::verification(const Figure *figure,
						short int newJ, short int newI) const{
	assert(figure != 0);
	//если попали за границы поля
	if (newI+2-figure->getBorder().lX < 0 || newI+2+figure->getBorder().rX > Settings::boardActiveWidth-1)
		return (false);
	if (newJ+2-figure->getBorder().uY  < 0 || newJ+2+figure->getBorder().dY > Settings::boardActiveHeight-1)
		return (false);

	//если натолкнулись на припятствие
	for (int j = 0; j < Figure::sizeFigure; ++j)
		for (int i = 0; i < Figure::sizeFigure; ++i)
			if (figure->getArrayFigure(j, i))
				if (boardArray[j + newJ][i + newI] != board_None &&
						boardArray[j + newJ][i + newI] != board_Down)
					return (false);
	return (true);
}
//--------------------------------------------
// return true if firure can not dawn (check "activeFigureY +1")
bool Board::notDownsFigure(const Figure *figure) const{
	assert(figure != 0);
	if (!verification(figure, activeFigureY +1, activeFigureX))
		return (true);
	return (false);
}
//--------------------------------------------
// in process... переделать костыли
// 1 - звук падения, 2 - звук сброса, 3 - конец игры
unsigned char Board::logic(){
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
			figureInBoard(activeFigure);
			return (3);
		}
		figureInBoard(activeFigure);//выкатили новую фигуру на поле
		return(rezult);
	}
	else{
		downFigure();
		return (0);
	}
}
//--------------------------------------------
// end game
void Board::gameOver(){
	// проверить что подчистил все сотояния
	points = 0;
	resetBoard();
}
//--------------------------------------------
bool Board::getNextFigure(int j, int i) const{
	assert(j >= 0 && j < Figure::sizeFigure);
	assert(i >= 0 && i < Figure::sizeFigure);
	return (nextFigure->getArrayFigure(j, i));
}
//--------------------------------------------
// index "next figure"
unsigned long int Board::getNextFigureId() const{
	return (nextFigureId);
}
//--------------------------------------------
// Search full rows, reset it and shift
bool Board::lowerRow(){
	bool check, rezult(false);
	for (int j = 0; j < Settings::boardActiveHeight; ++j){
		check = true;
		for (int i = 0; i < Settings::boardActiveWidth; ++i){
			if (boardArray[j][i] != board_Fixed)
				check = false;
		}
		if (check){
			rezult = true;
			for (int i = Settings::boardActiveWidth-1; i >= 0; --i)
				boardArray[j][i] = board_None;
			RowsDown(j);
			++points;
		}
	}
	return (rezult);
}
//--------------------------------------------
//down rows [y-1..0] to [y..1]
void Board::RowsDown(int y){
	for (int j = y-1; j >= 0; --j){
		for (int i = Settings::boardActiveWidth-1; i >= 0; --i)
			boardArray[j+1][i] = boardArray[j][i];
	}
}
//--------------------------------------------
unsigned int Board::getPoints() const{
	return (points);
}
//--------------------------------------------
