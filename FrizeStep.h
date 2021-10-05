#pragma once
#include <map>
#include <list>
#include "Matrix.h"

class FrizeStep
{
public:
	bool active; // активный или неактивный путь: активный, когда самый короткий, то есть waylength = min;
	std::map<int, int> stepWayPair; // путь, которому соответствует его длина, его матрица 
	//int waylenght; // длина данного маршрута
	Matrix matrixStepCity; // матрица данного шага 
	std::list<std::pair<int, int>> stepfiltrWayPair;// массив пар запоминания (для блокирования неугодных маршрутов).

public:
	/*void AddNextCity( ... );
	void CloneFrizeNegateCity();*/
	
	void SwapActive(FrizeStep& newActive);
};

