#pragma once

#include <iostream>
#include <map>
#include "Matrix.h"


namespace BnB
{
	
		int maxi = 0;
		int maxj = 0;
		std::vector<int> way;
	
		int zerosPower(Matrix inpMatrix)
		{
			int max = -1;
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
			if (max < 0)
			{
				std::cout << "\nmaxSum was not calculated";
				max = 0;
				for (int i = 0; i < inpMatrix.matrix.size(); i++)
				{
					for (int j = 0; j < inpMatrix.matrix.size(); j++)
					{
						if (inpMatrix.vertHeading[i] != inpMatrix.vertHeading[j])
						{
							maxi = i;
							maxj = j;
							goto loop;
						}
					}
				}
			}
		loop:                                                                          
			std::cout << " \nmaxSum = " << max << ". Row number " << inpMatrix.vertHeading[maxi] << " & Col number " << inpMatrix.horzHeading[maxj] << "\n";
			return max;

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
			intoOriginalMatrix.deleteRow(maxi);
			intoOriginalMatrix.deleteCol(maxj);
			return intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin();
		}

		void step1(Matrix& originalMatrix)// передаём копию матрицы?
		{
			originalMatrix.printM();

			originalMatrix.fsummaVertMin();
			originalMatrix.globalRowReduction();
			std::cout << "globalRowReduction\n ";
			originalMatrix.printM();

			originalMatrix.fsummaHorzMin();
			originalMatrix.globalColReduction();
			std::cout << "globalColReduction\n ";
			originalMatrix.printM();

			originalMatrix.allbound = originalMatrix.lowerBound();

			std::map<int, int> wayPair;
			while (originalMatrix.matrix.size() != 0)
			{
				originalMatrix.globalRowReduction();
				originalMatrix.globalColReduction();
				maxi = 0;
				maxj = 0;
				zerosPower(originalMatrix);
				Matrix copyMatrix(originalMatrix);// копирую матрицу, чтобы при сравнении корневых границ (при использовании функции rightway) метод не менял матрицу
				int timeBoundLeft = (originalMatrix.allbound + originalMatrix.minInRow(maxi) + originalMatrix.minInRow(maxj));

				if (timeBoundLeft < BnB::rightway(copyMatrix))
				{
					originalMatrix.matrix[maxi][maxj] = -1;
					std::cout << "После левого пути матрица равняется:\n";
					originalMatrix.printM();
					originalMatrix.allbound += timeBoundLeft;

				}
				else
				{
					//originalMatrix.matrix[maxj][maxi] = -1; // избавляемся от повтора (неправильный вариант) 

					for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
					{
						for (int j = 0; j < originalMatrix.matrix.size(); j++)
						{
							if ((originalMatrix.vertHeading[i] == originalMatrix.horzHeading[maxj]) && (originalMatrix.horzHeading[j] == originalMatrix.vertHeading[maxi]))
							{
								originalMatrix.matrix[i][j] = -1;
							}
						}
					}
						
					/*if (!way.empty() && (*(way.end() - 1) == originalMatrix.vertHeading.at(maxi)))
					{
						way.push_back(originalMatrix.horzHeading.at(maxj));
					}
					else if (way.size()>=2 && (originalMatrix.vertHeading.at(maxi)==originalMatrix.horzHeading.at(maxj)))
					{ }
					else
					{
						
					}*/

						//way.push_back(originalMatrix.vertHeading.at(maxi));
						//way.push_back(originalMatrix.horzHeading.at(maxj));

					wayPair.emplace(originalMatrix.vertHeading.at(maxi), originalMatrix.horzHeading.at(maxj));

					originalMatrix.allbound += BnB::rightway(originalMatrix); // сработал правый метод, удаляющий строки и столбцы
					if (originalMatrix.matrix.size() != 0)
					{
						std::cout << "После правого пути матрица равняется:\n";
						originalMatrix.printM();
					}
					else
					{
						std::cout << "Путь найден.\n";
					}
				}
			}

			//"склеиваем пары путей"
			way.push_back(wayPair.begin()->first);
			way.push_back(wayPair.begin()->second);
			for (int i = 1; i < wayPair.size(); i++)
			{
				for (int j = 1; j < wayPair.size(); j++)
				{
					if (way.at(i) == j)
					{
						way.push_back(wayPair[j]);
						break;
					}
				}
			}


			std::cout << " Цепочка передвижения: " << std::endl;
			for (std::vector<int>::iterator iter = way.begin(); iter != way.end(); iter++)
			{
				if ((iter+1) != way.end())
				{
					std::cout << ((*iter) + 1) << "->";
				}
				else
				{
					std::cout << ((*iter) + 1) << std::endl;
				}
			}
			//std::cout << way[0] << std::endl;
			std::cout << "Длина маршрута = " << originalMatrix.allbound << std::endl;

		}

		void excludeway(int to, int from, Matrix& originalMatrix)
		{
			originalMatrix.matrix[from][to] = -1;
		}

		void Addstep(int from, int to, Matrix& originalMatrix)
		{
			excludeway(from, to, originalMatrix);
			if (*(way.end()-1)== from)
			{
				way.push_back(to);
			}
			else
			{
				way.push_back(from);
				way.push_back(to);
			}
			
		}
}


	