#pragma once

#include <iostream>
#include <map>
#include <list>
#include "Matrix.h"
#include "FrizeStep.h"

namespace BnB // вычисляет нужный маршрут
{

	int maxi = 0; // индекс строки нулевой клетки с наибольшей оценкой
	int maxj = 0; // индекс столбца нулевой клетки с наибольшей оценкой
	std::vector<int> way; // вектор пути
	std::list<FrizeStep> alternatives; // 
	//std::vector<int> saveway;

	void firstRedaction(Matrix& originalMatrix)
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
	}

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
		//	std::cout << " \nmaxSum = " << max << ". Row number " << inpMatrix.vertHeading[maxi] << " & Col number " << inpMatrix.horzHeading[maxj] << "\n";
		return max;
	}

	//void leftway(Matrix intoOriginalMatrix, int bound) похоже можно обойтись без явной функции левого ветвления
	//{
	//	//int supposedBound1 = 0;
	//	
	//	//zerosPower(matrix);

	//	//return supposedBound1;
	//}

	int leftway(Matrix& intoOriginalMatrix)
	{
		intoOriginalMatrix.matrix[maxi][maxj] = -1;
		intoOriginalMatrix.allbound += intoOriginalMatrix.minInRow(maxi);
		intoOriginalMatrix.rowReduction(maxi, intoOriginalMatrix.minInRow(maxi));

		intoOriginalMatrix.allbound += intoOriginalMatrix.minInCol(maxj);
		intoOriginalMatrix.colReduction(maxj, intoOriginalMatrix.minInCol(maxj));

		return intoOriginalMatrix.allbound;
	}

	int rightway(Matrix& intoOriginalMatrix)
	{
		intoOriginalMatrix.deleteRow(maxi);
		intoOriginalMatrix.deleteCol(maxj);
		//	std::cout << "На данный момент ДЛИНА всего пути = " << intoOriginalMatrix.allbound << std::endl;
		intoOriginalMatrix.fsummaVertMin();
		intoOriginalMatrix.globalRowReduction();

		intoOriginalMatrix.fsummaHorzMin();
		intoOriginalMatrix.globalColReduction();

		intoOriginalMatrix.allbound += intoOriginalMatrix.lowerBound();
		//	std::cout << "На данный момент ДЛИНА всего пути = " << intoOriginalMatrix.allbound << std::endl;
		return intoOriginalMatrix.allbound/*intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin()*/; // Добавляем к ДЛИНЕ маршрута перед редукцией
	}
	
	void addPair(Matrix& intoOriginalMatrix, std::map<int, int>& intowayPair)
	{
		//if (intoOriginalMatrix.matrix.size() != 2) // работает всё также
		//{
		intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
		BnB::rightway(intoOriginalMatrix);
		//intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix); // сработал правый метод, удаляющий строки и столбцы


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


	void FiltrPair(std::list<std::pair<int, int>>& filtrWayPair, Matrix& originalMatrix)
	{
		for (auto it = filtrWayPair.begin(); it != filtrWayPair.end(); it++) // для матрицы 2х2 и 1х1 уже можно элементы не удалять
		{


			if (it->second == originalMatrix.vertHeading.at(maxi)) // исключаем подцикл (a b)(b c) => (a c) = -1 
			{
				it->second = originalMatrix.horzHeading.at(maxj);
				for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
				{
					for (int j = 0; j < originalMatrix.matrix.size(); j++)
					{
						if ((originalMatrix.horzHeading[j] == it->first) && (originalMatrix.vertHeading[i] == it->second))
						{

							originalMatrix.matrix[i][j] = -1;

						}
					}
				}

				// Объединить с двух сторон элементов filtrWayPair (Склейка)
				for (auto it2 = filtrWayPair.begin(); it2 != filtrWayPair.end(); it2++) // для матрицы 2х2 и 1х1 уже можно элементы не удалять
				{
					if (it->second == it2->first)
					{
						it->second = it2->second;
						filtrWayPair.erase(it2);
						if (filtrWayPair.size() == 0)
						{
							return;
						}
						for (int i2 = 0; i2 < originalMatrix.matrix.size(); i2++) // избавляемся от повтора
						{
							for (int j2 = 0; j2 < originalMatrix.matrix.size(); j2++)
							{
								if ((originalMatrix.horzHeading[j2] == it->first) && (originalMatrix.vertHeading[i2] == it->second))
								{
									originalMatrix.matrix[i2][j2] = -1;
									return; // Только что объединили, поэтому можно выходить из цикла
								}
							}
						}
					}
				}
			}

			if (it->first == originalMatrix.horzHeading.at(maxj))// исключаем подцикл (a b)(c a) => (c b) = -1 и смотрим возможность склейки элементов filtrWayPair
			{
				it->first = originalMatrix.vertHeading.at(maxi);

				// исключаем подцикл (a b)(c a) => (c b) = -1
				for (int i = 0; i < originalMatrix.matrix.size(); i++) // избавляемся от повтора
				{
					for (int j = 0; j < originalMatrix.matrix.size(); j++)
					{
						if ((originalMatrix.horzHeading[j] == it->first) && (originalMatrix.vertHeading[i] == it->second))
						{
							originalMatrix.matrix[i][j] = -1;
						}
					}
				}

				// Объединить с двух сторон элементов filtrWayPair (Склейка)
				for (auto it1 = filtrWayPair.begin(); it1 != filtrWayPair.end(); it1++) // для матрицы 2х2 и 1х1 уже можно элементы не удалять
				{
					if (it->first == it1->second)
					{
						it->first = it1->first;
						filtrWayPair.erase(it1);
						if (filtrWayPair.size() == 0)
						{
							return;
						}
						for (int i1 = 0; i1 < originalMatrix.matrix.size(); i1++) // избавляемся от повтора
						{
							for (int j1 = 0; j1 < originalMatrix.matrix.size(); j1++)
							{
								if ((originalMatrix.horzHeading[j1] == it->first) && (originalMatrix.vertHeading[i1] == it->second))
								{

									originalMatrix.matrix[i1][j1] = -1;
									return; // Только что объединили, поэтому можно выходить из цикла
								}
							}
						}
					}
				}

			}

		}
	}

	void RightOrEnd(Matrix& originalMatrix)
	{
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

	void BlockReverse(Matrix& originalMatrix) // если включаем (i j), то выключаем (j i)
	{
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
	}

	void realRightWay(Matrix& originalMatrix, std::map<int, int>& wayPair, std::list<std::pair<int, int>>& filtrWayPair)
	{
		BnB::BlockReverse(originalMatrix); // если включаем (i j), то выключаем (j i)

		for (auto it = filtrWayPair.begin(); it != filtrWayPair.end(); it++)
		{
			if (it->first == originalMatrix.horzHeading.at(maxj) || it->second == originalMatrix.vertHeading.at(maxi))
			{
				goto noAdd;
			}
		}
		filtrWayPair.push_back(std::make_pair(originalMatrix.vertHeading.at(maxi), originalMatrix.horzHeading.at(maxj)));
	noAdd:
		BnB::FiltrPair(filtrWayPair, originalMatrix); // сохраняем фильтрованный массив с парами и исключаем с его помощью ячейки, которые могут зациклить программу
		BnB::addPair(originalMatrix, wayPair); // включили ячейку в маршрут (пока не склеенный). 
		//( комментарий может быть актуален )* Работает с матрицей 2х2 по другому, чтобы исключить возможность добавления ячейки с индексом строки==индексу столбца  
	}

	void joinPairIntoLastWay(std::map<int, int>& wayPair) // Склеиваем пары в финальные
	{
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
	}

		// сравнивает Текущий шаг со всеми другими Самыми лучшими (самой короткой длиной маршрута и с самым большим количеством городов в цепи)
	void AnalizNextStep(FrizeStep& ourStep) 
	{
		int minwaylength = alternatives.begin()->waylenght; // инициализируем переменную минимального пути
		int maxchain = -1; // инициализируем переменную максимальной цепи (количества) городов для минимального пути
		auto nextStep = alternatives.begin(); // указатель на следующий маршрут

		for (auto it = alternatives.begin(); it != alternatives.end(); it++) // цикл нахождения минимальной длины города 
		{
			if (it->waylenght < minwaylength)
			{
					minwaylength = it->waylenght;
			}
		}

		for (auto it = alternatives.begin(); it != alternatives.end(); it++) // цикл нахождения максимальной цепочки пути среди цепочек с минимальной длиной 			{
		{
			if ((it->waylenght == minwaylength) && (it->stepWayPair.size() > maxchain))
			{
				maxchain = it->stepWayPair.size();
			}
		}

		for (auto it = alternatives.begin(); it != alternatives.end(); it++) // цикл нахождения лучшего города (с минимальной длиной и для неё максимальной цепью)
		{
			if ((ourStep.waylenght == it->waylenght) && (maxchain == it->stepWayPair.size()))
			{
				nextStep = it; 
				ourStep.SwapActive(*nextStep); // Теперь это активный путь
				break; // по идее нам не важно, какая из цепочек с адинаковой длиной и равным числом городов будет выбрана для продолжения
			}
		}

	}

	void AddNextCityLeft()
	{

	}

	void AddNextCityRight(FrizeStep rightFrizeNotActive) // КОПИРУЕМ для создания нового элемента массива FrizeStep (неактивного)
	{
		
	}

		void step1(Matrix& originalMatrix)// передаём копию матрицы?
		{
			firstRedaction(originalMatrix);
			FrizeStep firstFrize; 
			firstFrize.matrixStepCity = originalMatrix; firstFrize.active = true;
			std::map<int, int> wayPair;
			std::list<std::pair<int, int>> filtrWayPair;// нужен для массива запоминаня
			std::cout << "\n------------------------Начинаем шагать------------------------\n\n";

			while (originalMatrix.matrix.size() != 0)
			{
				maxi = 0;
				maxj = 0;
				zerosPower(originalMatrix);
				Matrix copyMatrix1(originalMatrix); // копирую матрицу, чтобы при сравнении корневых границ (при использовании функции leftway)  метод не менял матрицу
				Matrix copyMatrix2(originalMatrix); // копирую матрицу, чтобы при сравнении корневых границ (при использовании функции rightway) метод не менял матрицу

				if (leftway(copyMatrix1) < BnB::rightway(copyMatrix2)) // левый путь
				{
					AddNextCityRight(firstFrize);
					leftway(originalMatrix);
				}
				else // правый путь
				{
					realRightWay(originalMatrix, wayPair, filtrWayPair);

					RightOrEnd(originalMatrix); // при нулевой матрице выводим, что путь найден, иначе показываем чему равна матрица после правого пути
				}
			}

			//"склеиваем пары путей" 
			joinPairIntoLastWay(wayPair);
			wayAndLong(originalMatrix); // Путь и его длина 
		}

		/*
		//AnalizNextStep()
		std::cout << "После левого пути матрица равняется:\n";
		originalMatrix.printM();
		//std::cout << "На данный момент ДЛИНА всего пути = " << originalMatrix.allbound << std::endl;
		*/

		/*void excludeway(int to, int from, Matrix& originalMatrix)
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
			
		}*/
}


	