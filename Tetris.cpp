//Tetris.cpp
#include "myHeader.h"
#include "Tetris.h"
#include <cassert>

// Settings
const std::string Settings::pathNone = "pictures_40/None.png";
const std::string Settings::pathDown = "pictures_40/Down.png";
const std::string Settings::pathFixed = "pictures_40/Fixed.png";
const std::string Settings::pathWhite = "pictures_40/White.png";


void cleaner_sp(Shape* object){
	Vet::myError("опа!\n");
}

//Grid===========================================
Board::Board()://activeFigure(new Figure), nextFigure(new Figure(static_cast<figure_Type>(0))),
	activeShape( objectPool.creatObject()),
	nextShape(objectPool.creatObject()), turneShape(0),
	activeShapeX(3), activeShapeY(0), nextShapeId(1), points(0),
	renderBoard(true), renderMenu(true), renderNextShape(true){

//	activeFigure.reset(objectPool.creatObject());
//	nextFigure.reset(objectPool.creatObject());

	activeShapeY = activeShape->getBorder().uY - 2;// поправка если есть пустоты
	shapeInBoard(activeShape);
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
void Board::turnShape(){
	turneShape = objectPool.creatObject();
	if ( !activeShape->cloneTurned(turneShape) ){
		objectPool.deleteObject(turneShape);
		return;
	}
	if ( verification(turneShape, activeShapeY , activeShapeX) ){
		shapeOutBoard(activeShape);
		objectPool.deleteObject(activeShape);
		activeShape = turneShape;
		shapeInBoard(activeShape);
		renderBoard = true;
	}
	else
		if ( verification(turneShape, activeShapeY , activeShapeX +1) ){
			shapeOutBoard(activeShape);
			++activeShapeX;
			objectPool.deleteObject(activeShape);
			activeShape = turneShape;
			shapeInBoard(activeShape);
			renderBoard = true;
		}
		else
			if ( verification(turneShape, activeShapeY , activeShapeX -1) ){
				shapeOutBoard(activeShape);
				--activeShapeX;
				objectPool.deleteObject(activeShape);
				activeShape = turneShape;
				shapeInBoard(activeShape);
				renderBoard = true;
			}
			else
				if ( verification(turneShape, activeShapeY +1 , activeShapeX) ){
					shapeOutBoard(activeShape);
					++activeShapeY;
					objectPool.deleteObject(activeShape);
					activeShape = turneShape;
					shapeInBoard(activeShape);
					renderBoard = true;
				}
				else
					if ( verification(turneShape, activeShapeY , activeShapeX +2) ){
						shapeOutBoard(activeShape);
						activeShapeX+=2;
						objectPool.deleteObject(activeShape);
						activeShape = turneShape;
						shapeInBoard(activeShape);
						renderBoard = true;
					}
					else
						if ( verification(turneShape, activeShapeY , activeShapeX -2) ){
							shapeOutBoard(activeShape);
							activeShapeX-=2;
							objectPool.deleteObject(activeShape);
							activeShape = turneShape;
							shapeInBoard(activeShape);
							renderBoard = true;
						}
						else
							if ( verification(turneShape, activeShapeY +2 , activeShapeX) ){
								shapeOutBoard(activeShape);
								activeShapeY+=2;
								objectPool.deleteObject(activeShape);
								activeShape = turneShape;
								shapeInBoard(activeShape);
								renderBoard = true;
							}
}
//--------------------------------------------
// acceleration down for active figure
void Board::downShape(){
	if (verification(activeShape, activeShapeY +1, activeShapeX)){
		shapeOutBoard(activeShape);
		++activeShapeY;
		shapeInBoard(activeShape);
		renderBoard = true;
	}
}
//--------------------------------------------
// moving active figure to left
void Board::leftShape(){
	if (verification(activeShape, activeShapeY, activeShapeX - 1)){
		shapeOutBoard(activeShape);
		--activeShapeX;
		shapeInBoard(activeShape);
		renderBoard = true;
	}
}
//--------------------------------------------
// moving active figure to right
void Board::rightShape(){
	if (verification(activeShape, activeShapeY, activeShapeX + 1)){
		shapeOutBoard(activeShape);
		++activeShapeX;
		shapeInBoard(activeShape);
		renderBoard = true;
	}
}
//--------------------------------------------
// mapping figure to gridArray as grid_Down
void Board::shapeInBoard(const Shape* figure){
	assert(figure != 0);
	for (int j = 0; j < Shape::sizeShape; ++j)
		for (int i = 0; i < Shape::sizeShape; ++i)
			if (figure->getArrayShape(j, i))
				boardArray[j + activeShapeY][i + activeShapeX] = board_Down;
	renderBoard = true;
}
//--------------------------------------------
// mapping figure to gridArray as grid_None
void Board::shapeOutBoard(const Shape *figure){
	assert(figure != 0);
	for (int j = 0; j < Shape::sizeShape; ++j)
		for (int i = 0; i < Shape::sizeShape; ++i)
			if (figure->getArrayShape(j, i))
				boardArray[j + activeShapeY][i + activeShapeX] = board_None;
	renderBoard = true;
}
//--------------------------------------------
// mapping figure to gridArray as grid_Fixed
void Board::shapeFixed(const Shape *figure){
	for (int j = 0; j < Shape::sizeShape; ++j)
		for (int i = 0; i < Shape::sizeShape; ++i)
			if (figure->getArrayShape(j, i))
				boardArray[j + activeShapeY][i + activeShapeX] = board_Fixed;
	renderBoard = true;
}
//--------------------------------------------
// check the display in an array of shapes
bool Board::verification(const Shape *figure,
						short int newJ, short int newI) const{
	assert(figure != 0);
	//если попали за границы поля
	if (newI+2-figure->getBorder().lX < 0 || newI+2+figure->getBorder().rX > Settings::boardActiveWidth-1)
		return (false);
	if (newJ+2-figure->getBorder().uY  < 0 || newJ+2+figure->getBorder().dY > Settings::boardActiveHeight-1)
		return (false);

	//если натолкнулись на припятствие
	for (int j = 0; j < Shape::sizeShape; ++j)
		for (int i = 0; i < Shape::sizeShape; ++i)
			if (figure->getArrayShape(j, i))
				if (boardArray[j + newJ][i + newI] != board_None &&
						boardArray[j + newJ][i + newI] != board_Down)
					return (false);
	return (true);
}
//--------------------------------------------
// return true if firure can not dawn (check "activeFigureY +1")
bool Board::notDownsShape(const Shape *figure) const{
	assert(figure != 0);
	if (!verification(figure, activeShapeY +1, activeShapeX))
		return (true);
	return (false);
}
//--------------------------------------------
// in process... переделать костыли
// 1 - звук падения, 2 - звук сброса, 3 - конец игры
unsigned char Board::logic(){
	if (notDownsShape(activeShape))// если не можем двигать, двигаем
	{
		unsigned char rezult(1);
		shapeFixed(activeShape);//зафиксировали
		if (lowerRow())//сбросилось?
			rezult = 2;
		objectPool.deleteObject(activeShape);
		activeShape = nextShape;//вытащили следующую фигуру
		activeShapeY = activeShape->getBorder().uY - 2;//стандартая корректировка от пустот
		activeShapeX = 3;
		nextShape = objectPool.creatObject();// обновили новую фигуру
		renderNextShape = true;
		++nextShapeId; // счетчик новой фигуры
		if (notDownsShape(activeShape)){//если она не лезит в стакан, то конец
			gameOver();
			shapeInBoard(activeShape);
			return (3);
		}
		shapeInBoard(activeShape);//выкатили новую фигуру на поле
		return(rezult);
	}
	else{
		downShape();
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
bool Board::getNextShape(int j, int i) const{
	assert(j >= 0 && j < Shape::sizeShape);
	assert(i >= 0 && i < Shape::sizeShape);
	return (nextShape->getArrayShape(j, i));
}
//--------------------------------------------
// index "next figure"
unsigned long int Board::getNextShapeId() const{
	return (nextShapeId);
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
