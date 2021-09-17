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

	//+
	/*Matrix firstMatrix(0, 50, 4);
	firstMatrix.matrix[0][0] = -1; firstMatrix.matrix[0][1] = 20; firstMatrix.matrix[0][2] = 16; firstMatrix.matrix[0][3] = 39;
	firstMatrix.matrix[1][0] = 48; firstMatrix.matrix[1][1] = -1; firstMatrix.matrix[1][2] = 24; firstMatrix.matrix[1][3] = 48; 
	firstMatrix.matrix[2][0] = 36; firstMatrix.matrix[2][1] = 41; firstMatrix.matrix[2][2] = -1; firstMatrix.matrix[2][3] = 24; 
	firstMatrix.matrix[3][0] = 34; firstMatrix.matrix[3][1] = 3;  firstMatrix.matrix[3][2] = 32; firstMatrix.matrix[3][3] = -1;
	*/

	//Ã¿“–»÷¿ 6’6 —œ≈÷»‘»◊≈— »…!
	/*
	Matrix firstMatrix(0, 50, 6);
	firstMatrix.matrix[0][0] = -1;	 firstMatrix.matrix[0][1] = 6;		firstMatrix.matrix[0][2] = 11;	firstMatrix.matrix[0][3] = 16;	 firstMatrix.matrix[0][4] = 3;		 firstMatrix.matrix[0][5] = 8;
	firstMatrix.matrix[1][0] = 1;	 firstMatrix.matrix[1][1] = -1;		firstMatrix.matrix[1][2] = 12;	firstMatrix.matrix[1][3] = 17;	 firstMatrix.matrix[1][4] = 4;		 firstMatrix.matrix[1][5] = 9;
	firstMatrix.matrix[2][0] = 2;	 firstMatrix.matrix[2][1] = 7;		firstMatrix.matrix[2][2] = -1;	firstMatrix.matrix[2][3] = 18;	 firstMatrix.matrix[2][4] = 5;		 firstMatrix.matrix[2][5] = 10;
	firstMatrix.matrix[3][0] = 3;	 firstMatrix.matrix[3][1] = 8;		firstMatrix.matrix[3][2] = 13;	firstMatrix.matrix[3][3] = -1;	 firstMatrix.matrix[3][4] = 6;		 firstMatrix.matrix[3][5] = 11;
	firstMatrix.matrix[4][0] = 4;	 firstMatrix.matrix[4][1] = 9;		firstMatrix.matrix[4][2] = 14;	firstMatrix.matrix[4][3] = 1;	 firstMatrix.matrix[4][4] = -1;		 firstMatrix.matrix[4][5] = 12;
	firstMatrix.matrix[5][0] = 5;	 firstMatrix.matrix[5][1] = 10;		firstMatrix.matrix[5][2] = 15;	firstMatrix.matrix[5][3] = 2;	 firstMatrix.matrix[5][4] = 7;		 firstMatrix.matrix[5][5] = -1;
	*/

	//+
	/*Matrix firstMatrix(0, 50, 6);
	firstMatrix.matrix[0][0] = -1;	 firstMatrix.matrix[0][1] = 49;		firstMatrix.matrix[0][2] = 45;	firstMatrix.matrix[0][3] = 42;	 firstMatrix.matrix[0][4] = 41;		 firstMatrix.matrix[0][5] = 43;
	firstMatrix.matrix[1][0] = 30;	 firstMatrix.matrix[1][1] = -1;		firstMatrix.matrix[1][2] = 20;	firstMatrix.matrix[1][3] = 33;	 firstMatrix.matrix[1][4] = 40;		 firstMatrix.matrix[1][5] = 35;
	firstMatrix.matrix[2][0] = 24;	 firstMatrix.matrix[2][1] = 26;		firstMatrix.matrix[2][2] = -1;	firstMatrix.matrix[2][3] = 25;	 firstMatrix.matrix[2][4] = 22;		 firstMatrix.matrix[2][5] = 26;
	firstMatrix.matrix[3][0] = 19;	 firstMatrix.matrix[3][1] = 36;		firstMatrix.matrix[3][2] = 25;	firstMatrix.matrix[3][3] = -1;	 firstMatrix.matrix[3][4] = 18;		 firstMatrix.matrix[3][5] = 43;
	firstMatrix.matrix[4][0] = 19;	 firstMatrix.matrix[4][1] = 18;		firstMatrix.matrix[4][2] = 18;	firstMatrix.matrix[4][3] = 12;	 firstMatrix.matrix[4][4] = -1;		 firstMatrix.matrix[4][5] = 25;
	firstMatrix.matrix[5][0] = 16;	 firstMatrix.matrix[5][1] = 47;		firstMatrix.matrix[5][2] = 31;	firstMatrix.matrix[5][3] = 14;	 firstMatrix.matrix[5][4] = 8;		 firstMatrix.matrix[5][5] = -1;
	*/

	// - Ï‡ÚËˆ‡ 6ı6
	Matrix firstMatrix(0, 50, 6);
	firstMatrix.matrix[0][0] = -1;	 firstMatrix.matrix[0][1] = 4;		firstMatrix.matrix[0][2] = 4;	firstMatrix.matrix[0][3] = 5;	 firstMatrix.matrix[0][4] = 4;		 firstMatrix.matrix[0][5] = 3;
	firstMatrix.matrix[1][0] = 2;	 firstMatrix.matrix[1][1] = -1;		firstMatrix.matrix[1][2] = 7;	firstMatrix.matrix[1][3] = 1;	 firstMatrix.matrix[1][4] = 1;		 firstMatrix.matrix[1][5] = 6;
	firstMatrix.matrix[2][0] = 2;	 firstMatrix.matrix[2][1] = 3;		firstMatrix.matrix[2][2] = -1;	firstMatrix.matrix[2][3] = 9;	 firstMatrix.matrix[2][4] = 4;		 firstMatrix.matrix[2][5] = 5;
	firstMatrix.matrix[3][0] = 1;	 firstMatrix.matrix[3][1] = 3;		firstMatrix.matrix[3][2] = 2;	firstMatrix.matrix[3][3] = -1;	 firstMatrix.matrix[3][4] = 3;		 firstMatrix.matrix[3][5] = 1;
	firstMatrix.matrix[4][0] = 7;	 firstMatrix.matrix[4][1] = 4;		firstMatrix.matrix[4][2] = 1;	firstMatrix.matrix[4][3] = 1;	 firstMatrix.matrix[4][4] = -1;		 firstMatrix.matrix[4][5] = 4;
	firstMatrix.matrix[5][0] = 2;	 firstMatrix.matrix[5][1] = 3;		firstMatrix.matrix[5][2] = 4;	firstMatrix.matrix[5][3] = 7;	 firstMatrix.matrix[5][4] = 9;		 firstMatrix.matrix[5][5] = -1;
	

	//+ Ï‡ÚËˆ‡ 5ı5 
	/*Matrix firstMatrix(0, 50, 5);
	firstMatrix.matrix[0][0] = -1; firstMatrix.matrix[0][1] = 90; firstMatrix.matrix[0][2] = 80; firstMatrix.matrix[0][3] = 40; firstMatrix.matrix[0][4] = 100;
	firstMatrix.matrix[1][0] = 60; firstMatrix.matrix[1][1] = -1; firstMatrix.matrix[1][2] = 40; firstMatrix.matrix[1][3] = 50; firstMatrix.matrix[1][4] = 70;
	firstMatrix.matrix[2][0] = 50; firstMatrix.matrix[2][1] = 30; firstMatrix.matrix[2][2] = -1; firstMatrix.matrix[2][3] = 60; firstMatrix.matrix[2][4] = 20;
	firstMatrix.matrix[3][0] = 10; firstMatrix.matrix[3][1] = 70; firstMatrix.matrix[3][2] = 20; firstMatrix.matrix[3][3] = -1; firstMatrix.matrix[3][4] = 50;
	firstMatrix.matrix[4][0] = 20; firstMatrix.matrix[4][1] = 40; firstMatrix.matrix[4][2] = 50; firstMatrix.matrix[4][3] = 20; firstMatrix.matrix[4][4] = -1;
	*/


	BnB::step1(firstMatrix);

}