#pragma once

#include "Matrix.h"
#include "iostream"

namespace BnB
{
	
		int maxi = 0;
		int maxj = 0;

	
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
			std::cout << " \nmaxSum = " << max << " " << maxi << " row and " << maxj << " col\n";
			return max;

			/*for (auto iter = matrix.begin(); iter != matrix.end(); iter++)
			{
				for (auto it = iter->begin(); it != iter->end(); it++)
				{
					if ()
				}

			}*/

		}

		//void leftway(Matrix intoOriginalMatrix, int bound) похоже можно обойтись без явной функции левого ветвления
		//{
		//	//int supposedBound1 = 0;
		//	
		//	//zerosPower(matrix);

		//	//return supposedBound1;
		//}

		int rightway(Matrix& intoOriginalMatrix)
		{
			//intoOriginalMatrix.matrix[maxj][maxi];
			intoOriginalMatrix.deleteRow(maxi);
			intoOriginalMatrix.deleteCol(maxj);

			intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin();//	intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin();

			return intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin();
		}

		void step1(Matrix& originalMatrix)// передаём копию матрицы?
		{
			//bound = matrix1.lowerBound();
			maxi = 0;
			maxj = 0;
			zerosPower(originalMatrix);
			Matrix copyMatrix(originalMatrix);// копирую матрицу, чтобы при сравнении корневых границ метод не менял матрицу
			int timeBoundLeft = (originalMatrix.allbound + originalMatrix.minInRow(maxi) + originalMatrix.minInRow(maxj));

			if (timeBoundLeft/*BnB::leftway(originalMatrix)*/ < BnB::rightway(copyMatrix))
			{
				originalMatrix.matrix[maxi][maxj] = -1;
				std::cout << "После левого пути матрица равняется:\n";
				originalMatrix.printM();
				originalMatrix.allbound += (copyMatrix.minInRow(maxi) + copyMatrix.minInRow(maxj));
			}
			else
			{
				originalMatrix.allbound += BnB::rightway(originalMatrix); // сработал правый метод, удаляющий строки и столбцы
				std::cout << "После правого пути матрица равняется:\n";
				originalMatrix.printM();
			}
		}
}


	