#pragma once

#include "Matrix.h"
#include "iostream"

namespace BnB
{
	
	int zerosPower(Matrix inpMatrix)
	{
		int max = 0;
		int maxi;
		int maxj;
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

	int leftway(Matrix matrix)
	{
		int supposedBound1=0;

		zerosPower(matrix);

		return supposedBound1;
	}

	int rightway(Matrix matrix)
	{
		int supposedBound2=0;

		return supposedBound2;
	}

}
	void initializingBound(Matrix originalMatrix, int bound) // инициализируем корневую нижнюю границу
	{
		bound = originalMatrix.lowerBound();
	}

	void step1(Matrix originalMatrix, int bound)// передаём копию матрицы?
	{
		//bound = matrix1.lowerBound();

		if (BnB::leftway(originalMatrix) <= BnB::rightway(originalMatrix))
		{
			bound += BnB::leftway(originalMatrix);
		}
		else
		{
			bound += BnB::rightway(originalMatrix);
		}

	}

	