#pragma once

#include <iostream>
#include <map>
#include <list>
#include "Matrix.h"


namespace BnB
{
	
		int maxi = 0; // индекс строки нулевой клетки с наибольшей оценкой
		int maxj = 0; // индекс столбца нулевой клетки с наибольшей оценкой
		std::vector<int> way; // вектор пути
		std::vector<int> saveway;
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
				//std::cout << "\nmaxSum was not calculated";
				max = 0;
				for (int i = 0; i < inpMatrix.matrix.size(); i++)
				{
					for (int j = 0; j < inpMatrix.matrix.size(); j++)
					{
						//if (inpMatrix.vertHeading[i] != inpMatrix.vertHeading[j])
						if (inpMatrix.matrix[i][j] != -1)
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

		void addPair(Matrix& intoOriginalMatrix, std::map<int, int>& intowayPair)
		{
			//if (intoOriginalMatrix.matrix.size() != 2) // работает всё также
			//{
				intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
				intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix); // сработал правый метод, удаляющий строки и столбцы
			//}
			//else
			//{
			//	//for (int i =0;i<2;i++)
			//	
			//	if (intoOriginalMatrix.matrix[maxi][maxj] != -1) // если матрица не будет 2х2 
			//	{
			//		Matrix copyMass(intoOriginalMatrix);
			//		rightway(copyMass);
			//		if (copyMass.matrix[0][0] != -1) // работает всё также
			//		{
			//			intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
			//			intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix);
			//		}
			//		else // возьмём маршруты с другой диагонали
			//		{
			//			if (maxj == 0)
			//			{
			//				maxj++;
			//				intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
			//				intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix);
			//			}
			//			else if (maxi == 0)
			//			{
			//				maxi++;
			//				intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
			//				intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix);
			//			}
			//			else
			//			{
			//				maxj--;
			//				intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
			//				intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix);
			//				//std::cout << "Ошибка: правый нижний элемент не может равняться -1 и рассматри\n";
			//			}
			//		}
			//	}
			//}
			//return std::make_pair(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
		}

		void wayAndLong(Matrix& intoOriginalMatrix)
		{
			std::cout << " Цепочка передвижения: " << std::endl;
			for (std::vector<int>::iterator iter = way.begin(); iter != way.end(); iter++)
			{
				if ((iter + 1) != way.end())
				{
					std::cout << ((*iter) + 1) << "->";
				}
				else
				{
					std::cout << ((*iter) + 1) << std::endl;
				}
			}
			std::cout << "Длина маршрута = " << intoOriginalMatrix.allbound << std::endl;
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
			std::list<std::pair<int, int>> filtrWayPair;// нужен для массива запоминаня
			while (originalMatrix.matrix.size() != 0)
			{
				originalMatrix.globalRowReduction();
				originalMatrix.globalColReduction();
				originalMatrix.printM();
				maxi = 0;
				maxj = 0;
				zerosPower(originalMatrix);
				Matrix copyMatrix(originalMatrix);// копирую матрицу, чтобы при сравнении корневых границ (при использовании функции rightway) метод не менял матрицу
				int timeBoundLeft = (originalMatrix.allbound + originalMatrix.minInRow(maxi) + originalMatrix.minInRow(maxj));

				if (timeBoundLeft < BnB::rightway(copyMatrix)) // левый путь
				{
					originalMatrix.matrix[maxi][maxj] = -1;
					std::cout << "После левого пути матрица равняется:\n";
					originalMatrix.allbound += timeBoundLeft;
				}
				else // правый путь
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
					
					//for (auto it = wayPair.begin(); it != wayPair.end(); it++) // исключаем подцикл (a b)(b c) => (a c) = -1 
					//{
					//	if (originalMatrix.vertHeading.at(maxi) == (it->second))
					//	{
					//		for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
					//		{
					//			for (int j = 0; j < originalMatrix.matrix.size(); j++)
					//			{
					//				if ((originalMatrix.horzHeading[j] == it->first) && (originalMatrix.vertHeading[i] == originalMatrix.horzHeading[maxj]))
					//				{
					//					//if (saveway.size() == 0)
					//					//{
					//						originalMatrix.matrix[i][j] = -1;
					//					//}
					//				//	saveway.push_back(originalMatrix.horzHeading.at(maxj)); // зачем это?
					//				}
					//			}
					//		}
					//			
					//	}
					//}

					//for (auto it = wayPair.begin(); it != wayPair.end(); it++) // исключаем подцикл (a b)(b c) => (a c) = -1 
					//{
					//	if (originalMatrix.horzHeading.at(maxj) == (it->first))
					//	{
					//		for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
					//		{
					//			for (int j = 0; j < originalMatrix.matrix.size(); j++)
					//			{
					//				if ( (originalMatrix.horzHeading[j] == originalMatrix.vertHeading[maxi]) && (originalMatrix.vertHeading[i] == it->second) )
					//				{
					//					//if (saveway.size() == 0)
					//					//{
					//					originalMatrix.matrix[i][j] = -1;
					//					//}
					//					//	saveway.push_back(originalMatrix.horzHeading.at(maxj)); // зачем это?
					//				}
					//			}
					//		}

					//	}
					//}




					
						for (auto it = filtrWayPair.begin(); it != filtrWayPair.end(); it++)
						{
							if ( it->first == originalMatrix.horzHeading.at(maxj) || it->second == originalMatrix.vertHeading.at(maxi) )
							{								
								goto noAdd;
							}							
						}
					filtrWayPair.push_back(std::make_pair(originalMatrix.vertHeading.at(maxi), originalMatrix.horzHeading.at(maxj)));
					noAdd:


					for (auto it = filtrWayPair.begin(); it != filtrWayPair.end(); it++) // для матрицы 2х2 и 1х1 уже можно элементы не удалять
					{
								
						if (originalMatrix.horzHeading.at(maxj) == it->first)
						{
							it->first = originalMatrix.vertHeading.at(maxi);
							for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
							{
								for (int j = 0; j < originalMatrix.matrix.size(); j++)
								{
									if ((originalMatrix.horzHeading[j] == originalMatrix.vertHeading[maxi]) && (originalMatrix.vertHeading[i] == it->second))
									{
										//if (saveway.size() == 0)
										//{
										originalMatrix.matrix[i][j] = -1;
										//}
										//	saveway.push_back(originalMatrix.horzHeading.at(maxj)); // зачем это?
									}
								}
							}
						}
						if (originalMatrix.vertHeading.at(maxi) == it->second)
						{
							it->second = originalMatrix.horzHeading.at(maxj);
							for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
							{
								for (int j = 0; j < originalMatrix.matrix.size(); j++)
								{
									if ((originalMatrix.horzHeading[j] == it->first) && (originalMatrix.vertHeading[i] == originalMatrix.horzHeading[maxj]))
									{
										//if (saveway.size() == 0)
										//{
											originalMatrix.matrix[i][j] = -1;
										//}
									//	saveway.push_back(originalMatrix.horzHeading.at(maxj)); // зачем это?
									}
								}
							}
						}
					}
					std::cout << "Befor delete" << std::endl;
					originalMatrix.printM();
					BnB::addPair(originalMatrix, wayPair); // включили ячейку в маршрут (пока не склеенный). 
					//Работает с матрицей 2х2 по другому, чтобы исключить возможность добавления ячейки с индексом строки==индексу столбца  


					/*
					if (saveway.size() != 0)
					{
						for (int k = 0; k < saveway.size(); k++)
						{
							for (auto it = wayPair.begin(); it != wayPair.end(); it++)
							{

								if (originalMatrix.vertHeading.at(maxi) == (saveway[k]))
								{
									for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
									{
										for (int j = 0; j < originalMatrix.matrix.size(); j++)
										{
											if ((originalMatrix.horzHeading[i] == saveway[k]) && (originalMatrix.vertHeading[j] == originalMatrix.vertHeading[maxj]))
											{
												
													originalMatrix.matrix[j][i] = -1;
												saveway.push_back(originalMatrix.horzHeading.at(maxj));

											}
										}
									}
								}
							}
						}
					}
					*/



					//if (saveway[k] == originalMatrix.vertHeading.at(maxi))
					//{
					//	for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
					//	{
					//		for (int j = 0; j < originalMatrix.matrix.size(); j++)
					//		{
					//			if ((originalMatrix.horzHeading[i] == it->first) && (originalMatrix.vertHeading[j] == originalMatrix.vertHeading[maxj]))
					//			{
					//				if (saveway.size() == 0)
					//				{
					//					originalMatrix.matrix[j][i] = -1;
					//				}
					//				saveway.push_back(originalMatrix.horzHeading.at(maxj));
					//			}
					//		}
					//	}

					//originalMatrix.printM();

					


					if (originalMatrix.matrix.size() != 0)
					{
						std::cout << "После правого пути матрица равняется:\n";
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

			wayAndLong(originalMatrix); // Путь и его длина 
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


	