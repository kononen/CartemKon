#pragma once

#include "Matrix.h"
#include "iostream"

namespace BnB
{
	int maxi = 0;
	int maxj = 0;
	void step1(Matrix originalMatrix, int transmitbound)// передаём копию матрицы?
	{
		//bound = matrix1.lowerBound();
		int maxi = 0;
		int maxj = 0;
		int bound = transmitbound;// = zerosPower(originalMatrix) + 
		int addbound1 = zerosPower(originalMatrix);
		if (transmitbound + addbound1/*BnB::leftway(originalMatrix)*/ < BnB::rightway(originalMatrix))
		{
			originalMatrix.matrix[maxi][maxj] = -1;
			//
			//bound += /*BnB::leftway(originalMatrix)*/;
		}
		else
		{
			bound += BnB::rightway(originalMatrix);
		}

	}

	int zerosPower(Matrix inpMatrix)
	{
		int max = 0;
		//int maxi = 0;
		//int maxj = 0;
		for (int i = 0; i < inpMatrix.matrix.size(); i++)
		{
			for (int j = 0; j < inpMatrix.matrix.size(); j++)
			{
				if (inpMatrix.matrix[i][j] == 0)
				{
					inpMatrix.matrix[i][j] = -1;
					if (inpMatrix.minInRow(i) + inpMatrix.minInCol(j) > max)
					{
						max = inpMatrix.minInRow(i) + inpMatrix.minInCol(j);
						maxi = i;
						maxj = j;
					}
					inpMatrix.matrix[i][j] = 0;
				}
			}
		}
		std::cout << " \n maxSum = " << max << " " << maxi << " row and " << maxj << " col\n";
		return max;

		/*for (auto iter = matrix.begin(); iter != matrix.end(); iter++)
		{
			for (auto it = iter->begin(); it != iter->end(); it++)
			{
				if ()
			}

		}*/

	}

	void leftway(Matrix intoOriginalMatrix, int bound)
	{
		//int supposedBound1 = 0;
		
		//zerosPower(matrix);

		//return supposedBound1;
	}

	int rightway(Matrix intoOriginalMatrix)
	{
		int supposedBound2 = 0;

		intoOriginalMatrix.matrix[maxj][maxi];
		intoOriginalMatrix.deleteRow(maxi);
		intoOriginalMatrix.deleteCol(maxj);

		supposedBound2 = intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin();


		return supposedBound2;
	}

}
	void initializingBound(Matrix originalMatrix, int bound) // инициализируем корневую нижнюю границу
	{
		bound = originalMatrix.lowerBound();
	}



	