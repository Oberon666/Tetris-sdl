//Tetris.h
#ifndef TETRIS_H
#define TETRIS_H

#include <string>
#include <tr1/memory>

#include "TFigure.h"
#include "ObjectPool.h"

//--------------------------------------------
enum grid_Type{grid_None,
			   grid_Down,
			   grid_Fixed};
//--------------------------------------------
struct Settings{
	static const unsigned char gridActiveWidth = 10;
	static const unsigned char gridActiveHeight = 20;
	static const unsigned char gridMenuWidth = 7;
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

class Grid{
public:
	static Grid& instance();
	Grid();

	grid_Type getGridArray(unsigned int j, unsigned int i) const;

	unsigned char logic();
	void turnFigure();
	void leftFigure();
	void rightFigure();

	bool getNextFigure(int j, int i) const;
	unsigned long int getNextFigureId() const;
	unsigned int getPoints() const;

	//to optimize the rendering
	bool renderGrid;
	bool renderMenu;
	bool renderNextFigure;

	virtual ~Grid();

private:
	ObjectPool objectPool;

	grid_Type gridArray[Settings::gridActiveHeight][Settings::gridActiveWidth];
	unsigned int points;

	Figure* activeFigure;
	short int activeFigureX;
	short int activeFigureY;

	Figure* nextFigure;
	unsigned long int nextFigureId;

	Figure* turneFigure;

	void downFigure();
	void resetGrid();
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
	Grid(const Grid&);
	Grid& operator=(const Grid&);
};
//--------------------------------------------
#endif // TETRIS_H
