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
void cleaner_sp(Figure* object);

class Board{
public:
	static Board& instance();
	Board();

	board_Type getBoardArray(unsigned int j, unsigned int i) const;

	unsigned char logic();
	void turnFigure();
	void leftFigure();
	void rightFigure();

	bool getNextFigure(int j, int i) const;
	unsigned long int getNextFigureId() const;
	unsigned int getPoints() const;

	//to optimize the rendering
	bool renderBoard;
	bool renderMenu;
	bool renderNextFigure;

	virtual ~Board();

private:
	ObjectPool objectPool;

	board_Type boardArray[Settings::boardActiveHeight][Settings::boardActiveWidth];
	unsigned int points;

	Figure* activeFigure;
	short int activeFigureX;
	short int activeFigureY;

	Figure* nextFigure;
	unsigned long int nextFigureId;

	Figure* turneFigure;

	void downFigure();
	void resetBoard();
	void figureInGrid(const Figure *figure);
	void figureOutGrid(const Figure* figure);
	bool verification(const Figure* figure, short newJ, short newI) const;
	bool notDownsFigure(const Figure* figure) const;
	void figureFixed(const Figure *figure);
	void gameOver();
	bool lowerRow();
	void RowsDown(int y);

	void empty(Figure *some);

	//not used
	Board(const Board&);
	Board& operator=(const Board&);
};
//--------------------------------------------
#endif // TETRIS_H
