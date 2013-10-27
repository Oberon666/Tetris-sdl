//TFigure.cpp
#include "myHeader.h"
#include "TFigure.h"
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>

//--------------------------------------------
Figure::Figure(): color (0){
	srand (clock());
	int type = rand()%7;
	myType = static_cast<figure_Type>(type);
	filling(figure_Type(type));
}
//--------------------------------------------
Figure::Figure(figure_Type type): myType(type), color (0){
	filling(type);
}
//--------------------------------------------
bool Figure::cloneTurned(Figure* clone) const{
	if (myType != figure_Q){
		for (int j = 0; j < sizeFigure; ++j)
			for (int i = 0; i < sizeFigure; ++i)
				clone->arrayFigure[i][sizeFigure-1 - j] = arrayFigure[j][i];

		clone->border.rX = border.uY;
		clone->border.dY = border.rX;
		clone->border.uY = border.lX;
		clone->border.lX = border.dY;

		clone->myType = myType;
	}
	else{
		return (false);
//		for (int j = 0; j < sizeFigure; ++j)
//			for (int i = 0; i < sizeFigure; ++i)
//				clone->arrayFigure[j][i] = arrayFigure[j][i];

//		clone->border.rX = border.rX;
//		clone->border.dY = border.dY;
//		clone->border.uY = border.uY;
//		clone->border.lX = border.lX;
	}
	assert(clone->checFilling());
	return (true);
}
//--------------------------------------------
figure_Type Figure::getType() const{
	return (myType);
}
//--------------------------------------------
Figure::~Figure(){
	//std::cout<<" i dead" <<std::endl;
}
//--------------------------------------------
bool Figure::getArrayFigure(unsigned char j, unsigned char i) const{
	return (arrayFigure[j][i]);
}
//--------------------------------------------
Figure::Border Figure::getBorder() const{
	return (border);
}
//--------------------------------------------
unsigned char Figure::getColor() const{
	return (color);
}
//--------------------------------------------
void Figure::filling(figure_Type type){
	assert(type >= 0 && type <= figure_Max );
	switch (type){
		case  figure_T: shapesT(); break;
		case  figure_Q: shapesQ(); break;
		case  figure_I: shapesI(); break;
		case  figure_Z: shapesZ(); break;
		case  figure_S: shapesS(); break;
		case  figure_J: shapesJ(); break;
		case  figure_L: shapesL(); break;
		case  figure_Max: shapesMax(); break;
		default: exit(-1);
	}
	assert(checFilling());
}
//--------------------------------------------
void Figure::clear(){
	srand (clock());
	int type = rand()%7;
	myType = static_cast<figure_Type>(type);
	filling(figure_Type(type));

//	bool arrayT[sizeFigure][sizeFigure] ={
//		0,0,0,0,0,
//		0,0,0,0,0,
//		0,0,0,0,0,
//		0,0,0,0,0,
//		0,0,0,0,0};

//	for (int j = 0; j < sizeFigure; ++j)
//		for (int i = 0; i < sizeFigure; ++i)
//			arrayFigure[j][i] = arrayT[j][i];

//	border.dY = 0;
//	border.lX = 0;
//	border.rX = 0;
//	border.uY = 0;
}
//--------------------------------------------
bool Figure::checFilling(){
	if (arrayFigure[sizeFigure/2][sizeFigure/2] != 1)
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
		for(int i = 0; i < sizeFigure; ++i){
			if (arrayFigure[j][i] == true){
				u = 2 - j;
				j = 255;
				break;
			}
		}
	for (int i = 4; i > 2; --i)
		for(int j = 0; j < sizeFigure; ++j){
			if (arrayFigure[j][i] == true){
				r = i - 2;
				i = 0;
				break;
			}
		}
	for (int j = 4; j > 2; --j)
		for(int i = 0; i < sizeFigure; ++i){
			if (arrayFigure[j][i] == true){
				d = j - 2;
				j = 0;
				break;
			}
		}
	for (int i = 0; i < 2; ++i)
		for(int j = 0; j < sizeFigure; ++j){
			if (arrayFigure[j][i] == true){
				l = 2 - i;
				i = 255;
				break;
			}
		}

	if ( !(border.dY ==d && border.lX == l && border.rX == r && border.uY ==u) ){
		std::cout<<"error tupe " <<myType <<": " <<int(d) <<" " <<int(l) <<" " <<int(r) <<" " <<int(u) <<std::endl;
		return (false);
	}
	return (true);
}

//--------------------------------------------
void Figure::shapesT(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,0,1,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Figure::shapesQ(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,0,0,0,0,
		0,1,1,0,0,
		0,1,1,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 1;
	border.lX = 1;
	border.rX = 0;
	border.uY = 0;
	return;
}
//--------------------------------------------
void Figure::shapesI(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,0,0,0,0,
		1,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 2;
	border.rX = 1;
	border.uY = 0;
	return;
}
//--------------------------------------------
void Figure::shapesZ(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,1,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Figure::shapesS(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,0,1,1,0,
		0,1,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Figure::shapesJ(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Figure::shapesL(){
	bool arrayT[sizeFigure][sizeFigure] ={
		0,0,0,0,0,
		0,0,0,1,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 0;
	border.lX = 1;
	border.rX = 1;
	border.uY = 1;
	return;
}
//--------------------------------------------
void Figure::shapesMax(){
	bool arrayT[sizeFigure][sizeFigure] ={
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1};

	for (int j = 0; j < sizeFigure; ++j)
		for (int i = 0; i < sizeFigure; ++i)
			arrayFigure[j][i] = arrayT[j][i];

	border.dY = 2;
	border.lX = 2;
	border.rX = 2;
	border.uY = 2;
	return;
}
//--------------------------------------------
