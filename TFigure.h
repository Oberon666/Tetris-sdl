//TFigure.h
#ifndef TFIGURE_H
#define TFIGURE_H

#include <string>
//#include <tr1/memory>
#include <tr1/memory>

//--------------------------------------------
enum figure_Type{figure_T,
				 figure_Q,
				 figure_I,
				 figure_Z,
				 figure_S,
				 figure_J,
				 figure_L,
				 figure_Max};
//--------------------------------------------
class Figure{
private:
	struct Border{
		unsigned char lX;
		unsigned char rX;
		unsigned char uY;
		unsigned char dY;
	};

public:
	Figure();
	~Figure();
	Figure(figure_Type type);

	static const unsigned char sizeFigure = 5;

	bool getArrayFigure(unsigned char j, unsigned char i) const;
	figure_Type getType() const;
	bool cloneTurned(Figure *clone) const;
	Border getBorder() const;
	unsigned char getColor() const;
	void clear();

private:
	bool arrayFigure[sizeFigure][sizeFigure];
	figure_Type myType;
	Border border;
	unsigned char color;

	void filling(figure_Type type);
	bool checFilling();
	void shapesT();
	void shapesQ();
	void shapesI();
	void shapesZ();
	void shapesS();
	void shapesJ();
	void shapesL();
	void shapesMax();

	Figure& operator=(const Figure&);
	//Figure(const Figure& fig);

};
//--------------------------------------------
#endif // TFIGURE_H
