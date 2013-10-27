//myHeader.cpp

#include "myHeader.h"
#include <iostream>

namespace Vet {
//--------------------------------------------
void myError(const char* message, char *message2) {
	std::cout<<message <<": " <<message2 <<std::endl;
	return;
}
//--------------------------------------------
void myError(const char* message) {
	std::cout<<message <<std::endl;
	return;
}
//--------------------------------------------
void myTer(int i){
	myError("Не дели на ноль!\n");
	std::terminate();
}
//--------------------------------------------
}
