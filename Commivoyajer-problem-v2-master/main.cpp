#include <iostream>

#include "App.h"
#include "Matrix.h"
#include "Globals.h"
#include "BnB.h"

bool Globals::runInnitialized = false;

int main()
{
	std::setlocale(LC_ALL, "Rus");
	//App mainCycle = App();
	Matrix firstMatrix(0,50,10);

	/* матрица 6х6
	firstMatrix.matrix[0][0] = -1;	 firstMatrix.matrix[0][1] = 4;		firstMatrix.matrix[0][2] = 4;	firstMatrix.matrix[0][3] = 5;	 firstMatrix.matrix[0][4] = 4;		 firstMatrix.matrix[0][5] = 3;
	firstMatrix.matrix[1][0] = 2;	 firstMatrix.matrix[1][1] = -1;		firstMatrix.matrix[1][2] = 7;	firstMatrix.matrix[1][3] = 1;	 firstMatrix.matrix[1][4] = 1;		 firstMatrix.matrix[1][5] = 6;
	firstMatrix.matrix[2][0] = 2;	 firstMatrix.matrix[2][1] = 3;		firstMatrix.matrix[2][2] = -1;	firstMatrix.matrix[2][3] = 9;	 firstMatrix.matrix[2][4] = 4;		 firstMatrix.matrix[2][5] = 5;
	firstMatrix.matrix[3][0] = 1;	 firstMatrix.matrix[3][1] = 3;		firstMatrix.matrix[3][2] = 2;	firstMatrix.matrix[3][3] = -1;	 firstMatrix.matrix[3][4] = 3;		 firstMatrix.matrix[3][5] = 1;
	firstMatrix.matrix[4][0] = 7;	 firstMatrix.matrix[4][1] = 4;		firstMatrix.matrix[4][2] = 1;	firstMatrix.matrix[4][3] = 1;	 firstMatrix.matrix[4][4] = -1;		 firstMatrix.matrix[4][5] = 4;
	firstMatrix.matrix[5][0] = 2;	 firstMatrix.matrix[5][1] = 3;		firstMatrix.matrix[5][2] = 4;	firstMatrix.matrix[5][3] = 7;	 firstMatrix.matrix[5][4] = 9;		 firstMatrix.matrix[5][5] = -1;
	*/

	/*матрица 5х5
	firstMatrix.matrix[0][0] = -1; firstMatrix.matrix[0][1] = 90; firstMatrix.matrix[0][2] = 80; firstMatrix.matrix[0][3] = 40; firstMatrix.matrix[0][4] = 100;
	firstMatrix.matrix[1][0] = 60; firstMatrix.matrix[1][1] = -1; firstMatrix.matrix[1][2] = 40; firstMatrix.matrix[1][3] = 50; firstMatrix.matrix[1][4] = 70;
	firstMatrix.matrix[2][0] = 50; firstMatrix.matrix[2][1] = 30; firstMatrix.matrix[2][2] = -1; firstMatrix.matrix[2][3] = 60; firstMatrix.matrix[2][4] = 20;
	firstMatrix.matrix[3][0] = 10; firstMatrix.matrix[3][1] = 70; firstMatrix.matrix[3][2] = 20; firstMatrix.matrix[3][3] = -1; firstMatrix.matrix[3][4] = 50;
	firstMatrix.matrix[4][0] = 20; firstMatrix.matrix[4][1] = 40; firstMatrix.matrix[4][2] = 50; firstMatrix.matrix[4][3] = 20; firstMatrix.matrix[4][4] = -1;*/


	firstMatrix.printM();
	int k = 0;
	std::cout << "Min in " << k << " Row = " << firstMatrix.minInRow(k) << std::endl;
	std::cout << "Min in " << k << " Col = " << firstMatrix.minInCol(k) << std::endl;
	
	firstMatrix.fsummaVertMin();
	firstMatrix.globalRowReduction();
		std::cout << "globalRowReduction\n ";
	firstMatrix.printM();

	firstMatrix.fsummaHorzMin();
	firstMatrix.globalColReduction();
		std::cout << "globalColReduction\n ";
	firstMatrix.printM();

	firstMatrix.allbound = firstMatrix.lowerBound();


	BnB::step1(firstMatrix);

}