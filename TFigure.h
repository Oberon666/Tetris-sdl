//TFigure.h
#ifndef TFIGURE_H
#define TFIGURE_H

#include <string>

//--------------------------------------------
enum shape_Type{shape_T,
				shape_Q,
				shape_I,
				shape_Z,
				shape_S,
				shape_J,
				shape_L,
				shape_Max};
//--------------------------------------------
class Shape{
private:
	struct Border{
		unsigned char lX;
		unsigned char rX;
		unsigned char uY;
		unsigned char dY;
	};

public:
	Shape();
	~Shape();
	Shape(shape_Type type);

	static const unsigned char sizeShape = 5;

	bool getArrayShape(unsigned char j, unsigned char i) const;
	shape_Type getType() const;
	bool cloneTurned(Shape *clone) const;
	Border getBorder() const;
	unsigned char getColor() const;
	void clear();

private:
	bool arrayShape[sizeShape][sizeShape];
	shape_Type myType;
	Border border;
	unsigned char color;

	void filling(shape_Type type);
	bool checFilling();
	void shapeT();
	void shapeQ();
	void shapeI();
	void shapeZ();
	void shapeS();
	void shapeJ();
	void shapeL();
	void shapeMax();

	Shape& operator=(const Shape&);
};
//--------------------------------------------
#endif // TFIGURE_H
