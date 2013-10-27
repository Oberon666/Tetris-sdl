//TFigure.cpp
#include "myHeader.h"
#include "TFigure.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

//--------------------------------------------
Shape::Shape(): color (0){
	srand (clock());
	int type = rand()%7;
	myType = static_cast<shape_Type>(type);
	filling(shape_Type(type));
}
//--------------------------------------------
Shape::Shape(shape_Type type): myType(type), color (0){
	filling(type);
}
//--------------------------------------------
bool Shape::cloneTurned(Shape* clone) const{
	if (myType != shape_Q){
		for (int j = 0; j < sizeShape; ++j)
			for (int i = 0; i < sizeShape; ++i)
				clone->arrayShape[i][sizeShape-1 - j] = arrayShape[j][i];

		clone->border.rX = border.uY;
		clone->border.dY = border.rX;
		clone->border.uY = border.lX;
		clone->border.lX = border.dY;

		clone->myType = myType;
	}
	else{
		return (false);
	}
	assert(clone->checFilling());
	return (true);
}
//--------------------------------------------
shape_Type Shape::getType() const{
	return (myType);
}
//--------------------------------------------
Shape::~Shape(){}
//--------------------------------------------
bool Shape::getArrayShape(unsigned char j, unsigned char i) const{
	return (arrayShape[j][i]);
}
//--------------------------------------------
Shape::Border Shape::getBorder() const{
	return (border);
}
//--------------------------------------------
unsigned char Shape::getColor() const{
	return (color);
}
//--------------------------------------------
void Shape::filling(shape_Type type){
	assert(type >= 0 && type <= shape_Max );
	switch (type){
		case  shape_T: shapeT(); break;
		case  shape_Q: shapeQ(); break;
		case  shape_I: shapeI(); break;
		case  shape_Z: shapeZ(); break;
		case  shape_S: shapeS(); break;
		case  shape_J: shapeJ(); break;
		case  shape_L: shapeL(); break;
		case  shape_Max: shapeMax(); break;
		default: exit(-1);
	}
	assert(checFilling());
}
//--------------------------------------------
void Shape::clear(){
	srand (clock());
	int type = rand()%7;
	myType = static_cast<shape_Type>(type);
	filling(shape_Type(type));
}
//--------------------------------------------
bool Shape::checFilling(){
	if (arrayShape[sizeShape/2][sizeShape/2] != 1)
		return (false);

	if ( !(border.dY >= 0 && border.dY <= 2) )
		return (false);
	if ( !(border.lX >= 0 && border.lX <= 2) )
		return (false);
	if ( !(border.rX >= 0 && border.rX <= 2) )
		return (false);
	if ( !(border.uY >= 0 && border.uY <= 2) )
		return (false);

	unsigned char u(0),r(0),d(0),l(0);
	for (int j = 0; j < 2; ++j)
		for(int i = 0; i < sizeShape; ++i){
			if (arrayShape[j][i] == true){
				u = 2 - j;
				j = 255;
				break;
			}
		}
	for (int i = 4; i > 2; --i)
		for(int j = 0; j < sizeShape; ++j){
			if (arrayShape[j][i] == true){
				r = i - 2;
				i = 0;
				break;
			}
		}
	for (int j = 4; j > 2; --j)
		for(int i = 0; i < sizeShape; ++i){
			if (arrayShape[j][i] == true){
				d = j - 2;
				j = 0;
				break;
			}
		}
	for (int i = 0; i < 2; ++i)
		for(int j = 0; j < sizeShape; ++j){
			if (arrayShape[j][i] == true){
				l = 2 - i;
				i = 255;
				break;
			}
		}

	if ( !(border.dY ==d && border.lX == l && border.rX == r && border.uY ==u) ){
		std::cout<<"error type " <<myType <<": " <<int(d) <<" " <<int(l) <<" " <<int(r) <<" " <<int(u) <<std::endl;
		return (false);
	}
	return (true);
}

//--------------------------------------------
void Shape::shapeT(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,0,1,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Shape::shapeQ(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,0,0,0,0,
		0,1,1,0,0,
		0,1,1,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 1;
	border.lX = 1;
	border.rX = 0;
	border.uY = 0;
	return;
}
//--------------------------------------------
void Shape::shapeI(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,0,0,0,0,
		1,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 2;
	border.rX = 1;
	border.uY = 0;
	return;
}
//--------------------------------------------
void Shape::shapeZ(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,1,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Shape::shapeS(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,0,1,1,0,
		0,1,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Shape::shapeJ(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Shape::shapeL(){
	bool arrayT[sizeShape][sizeShape] ={
		0,0,0,0,0,
		0,0,0,1,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Shape::shapeMax(){
	bool arrayT[sizeShape][sizeShape] ={
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1};

	for (int j = 0; j < sizeShape; ++j)
		for (int i = 0; i < sizeShape; ++i)
			arrayShape[j][i] = arrayT[j][i];

	border.dY = 2;
	border.lX = 2;
	border.rX = 2;
	border.uY = 2;
	return;
}
//--------------------------------------------
