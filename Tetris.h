//Tetris.h
#ifndef TETRIS_H
#define TETRIS_H

#include <string>
#include <tr1/memory>

#include "TFigure.h"
#include "ObjectPool.h"

//--------------------------------------------
enum board_Type{board_None,
			   board_Down,
			   board_Fixed};
//--------------------------------------------
struct Settings{
	static const unsigned char boardActiveWidth = 10;
	static const unsigned char boardActiveHeight = 20;
	static const unsigned char boardMenuWidth = 7;
	static const unsigned short int sizePrimitive = 40;
	static const std::string pathNone;
	static const std::string pathDown;
	static const std::string pathFixed;
	static const std::string pathWhite;

private:
	Settings();
};
//--------------------------------------------
void cleaner_sp(Shape* object);

class Board{
public:
	static Board& instance();
	Board();

	board_Type getBoardArray(unsigned int j, unsigned int i) const;

	unsigned char logic();
	void turnShape();
	void leftShape();
	void rightShape();

	bool getNextShape(int j, int i) const;
	unsigned long int getNextShapeId() const;
	unsigned int getPoints() const;

	//to optimize the rendering
	bool renderBoard;
	bool renderMenu;
	bool renderNextShape;

	virtual ~Board();

private:
	ObjectPool objectPool;

	board_Type boardArray[Settings::boardActiveHeight][Settings::boardActiveWidth];
	unsigned int points;

	Shape* activeShape;
	short int activeShapeX;
	short int activeShapeY;

	Shape* nextShape;
	unsigned long int nextShapeId;

	Shape* turneShape;

	void downShape();
	void resetBoard();
	void shapeInBoard(const Shape *figure);
	void shapeOutBoard(const Shape* figure);
	bool verification(const Shape* figure, short newJ, short newI) const;
	bool notDownsShape(const Shape* figure) const;
	void shapeFixed(const Shape *figure);
	void gameOver();
	bool lowerRow();
	void RowsDown(int y);

	void empty(Shape *some);

	//not used
	Board(const Board&);
	Board& operator=(const Board&);
};
//--------------------------------------------
#endif // TETRIS_H
