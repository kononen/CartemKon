#pragma once

#include <iostream>
#include <map>
#include <list>
#include "Matrix.h"
#include "FrizeStep.h"

namespace BnB // ��������� ������ �������
{

	int maxi = 0; // ������ ������ ������� ������ � ���������� �������
	int maxj = 0; // ������ ������� ������� ������ � ���������� �������
	std::vector<int> way; // ������ ����
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

	//void leftway(Matrix intoOriginalMatrix, int bound) ������ ����� �������� ��� ����� ������� ������ ���������
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
		//	std::cout << "�� ������ ������ ����� ����� ���� = " << intoOriginalMatrix.allbound << std::endl;
		intoOriginalMatrix.fsummaVertMin();
		intoOriginalMatrix.globalRowReduction();

		intoOriginalMatrix.fsummaHorzMin();
		intoOriginalMatrix.globalColReduction();

		intoOriginalMatrix.allbound += intoOriginalMatrix.lowerBound();
		//	std::cout << "�� ������ ������ ����� ����� ���� = " << intoOriginalMatrix.allbound << std::endl;
		return intoOriginalMatrix.allbound/*intoOriginalMatrix.fsummaHorzMin() + intoOriginalMatrix.fsummaVertMin()*/; // ��������� � ����� �������� ����� ���������
	}
	
	void addPair(Matrix& intoOriginalMatrix, std::map<int, int>& intowayPair)
	{
		//if (intoOriginalMatrix.matrix.size() != 2) // �������� �� �����
		//{
		intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
		BnB::rightway(intoOriginalMatrix);
		//intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix); // �������� ������ �����, ��������� ������ � �������


	//}
	//else
	//{
	//	//for (int i =0;i<2;i++)
	//	
	//	if (intoOriginalMatrix.matrix[maxi][maxj] != -1) // ���� ������� �� ����� 2�2 
	//	{
	//		Matrix copyMass(intoOriginalMatrix);
	//		rightway(copyMass);
	//		if (copyMass.matrix[0][0] != -1) // �������� �� �����
	//		{
	//			intowayPair.emplace(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
	//			intoOriginalMatrix.allbound += BnB::rightway(intoOriginalMatrix);
	//		}
	//		else // ������ �������� � ������ ���������
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
	//				//std::cout << "������: ������ ������ ������� �� ����� ��������� -1 � ���������\n";
	//			}
	//		}
	//	}
	//}
	//return std::make_pair(intoOriginalMatrix.vertHeading.at(maxi), intoOriginalMatrix.horzHeading.at(maxj));
	}

	void wayAndLong(Matrix& intoOriginalMatrix)
	{
		std::cout << " ������� ������������: " << std::endl;
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
		std::cout << "����� �������� = " << intoOriginalMatrix.allbound << std::endl;
	}


	void FiltrPair(std::list<std::pair<int, int>>& filtrWayPair, Matrix& originalMatrix)
	{
		for (auto it = filtrWayPair.begin(); it != filtrWayPair.end(); it++) // ��� ������� 2�2 � 1�1 ��� ����� �������� �� �������
		{


			if (it->second == originalMatrix.vertHeading.at(maxi)) // ��������� ������� (a b)(b c) => (a c) = -1 
			{
				it->second = originalMatrix.horzHeading.at(maxj);
				for (int i = 0; i < originalMatrix.matrix.size(); i++) // ����������� �� �������
				{
					for (int j = 0; j < originalMatrix.matrix.size(); j++)
					{
						if ((originalMatrix.horzHeading[j] == it->first) && (originalMatrix.vertHeading[i] == it->second))
						{

							originalMatrix.matrix[i][j] = -1;

						}
					}
				}

				// ���������� � ���� ������ ��������� filtrWayPair (�������)
				for (auto it2 = filtrWayPair.begin(); it2 != filtrWayPair.end(); it2++) // ��� ������� 2�2 � 1�1 ��� ����� �������� �� �������
				{
					if (it->second == it2->first)
					{
						it->second = it2->second;
						filtrWayPair.erase(it2);
						if (filtrWayPair.size() == 0)
						{
							return;
						}
						for (int i2 = 0; i2 < originalMatrix.matrix.size(); i2++) // ����������� �� �������
						{
							for (int j2 = 0; j2 < originalMatrix.matrix.size(); j2++)
							{
								if ((originalMatrix.horzHeading[j2] == it->first) && (originalMatrix.vertHeading[i2] == it->second))
								{
									originalMatrix.matrix[i2][j2] = -1;
									return; // ������ ��� ����������, ������� ����� �������� �� �����
								}
							}
						}
					}
				}
			}

			if (it->first == originalMatrix.horzHeading.at(maxj))// ��������� ������� (a b)(c a) => (c b) = -1 � ������� ����������� ������� ��������� filtrWayPair
			{
				it->first = originalMatrix.vertHeading.at(maxi);

				// ��������� ������� (a b)(c a) => (c b) = -1
				for (int i = 0; i < originalMatrix.matrix.size(); i++) // ����������� �� �������
				{
					for (int j = 0; j < originalMatrix.matrix.size(); j++)
					{
						if ((originalMatrix.horzHeading[j] == it->first) && (originalMatrix.vertHeading[i] == it->second))
						{
							originalMatrix.matrix[i][j] = -1;
						}
					}
				}

				// ���������� � ���� ������ ��������� filtrWayPair (�������)
				for (auto it1 = filtrWayPair.begin(); it1 != filtrWayPair.end(); it1++) // ��� ������� 2�2 � 1�1 ��� ����� �������� �� �������
				{
					if (it->first == it1->second)
					{
						it->first = it1->first;
						filtrWayPair.erase(it1);
						if (filtrWayPair.size() == 0)
						{
							return;
						}
						for (int i1 = 0; i1 < originalMatrix.matrix.size(); i1++) // ����������� �� �������
						{
							for (int j1 = 0; j1 < originalMatrix.matrix.size(); j1++)
							{
								if ((originalMatrix.horzHeading[j1] == it->first) && (originalMatrix.vertHeading[i1] == it->second))
								{

									originalMatrix.matrix[i1][j1] = -1;
									return; // ������ ��� ����������, ������� ����� �������� �� �����
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
			std::cout << "����� ������� ���� ������� ���������:\n";
			originalMatrix.printM();
		}
		else
		{
			std::cout << "���� ������.\n";
		}
	}

	void BlockReverse(Matrix& originalMatrix) // ���� �������� (i j), �� ��������� (j i)
	{
		for (int i = 0; i < originalMatrix.matrix.size(); i++) // ����������� �� �������
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
		BnB::BlockReverse(originalMatrix); // ���� �������� (i j), �� ��������� (j i)

		for (auto it = filtrWayPair.begin(); it != filtrWayPair.end(); it++)
		{
			if (it->first == originalMatrix.horzHeading.at(maxj) || it->second == originalMatrix.vertHeading.at(maxi))
			{
				goto noAdd;
			}
		}
		filtrWayPair.push_back(std::make_pair(originalMatrix.vertHeading.at(maxi), originalMatrix.horzHeading.at(maxj)));
	noAdd:
		BnB::FiltrPair(filtrWayPair, originalMatrix); // ��������� ������������� ������ � ������ � ��������� � ��� ������� ������, ������� ����� ��������� ���������
		BnB::addPair(originalMatrix, wayPair); // �������� ������ � ������� (���� �� ���������). 
		//( ����������� ����� ���� �������� )* �������� � �������� 2�2 �� �������, ����� ��������� ����������� ���������� ������ � �������� ������==������� �������  
	}

	void joinPairIntoLastWay(std::map<int, int>& wayPair) // ��������� ���� � ���������
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

		// ���������� ������� ��� �� ����� ������� ������ ������� (����� �������� ������ �������� � � ����� ������� ����������� ������� � ����)
	void AnalizNextStep(FrizeStep& ourStep) 
	{
		int minwaylength = alternatives.begin()->waylenght; // �������������� ���������� ������������ ����
		int maxchain = -1; // �������������� ���������� ������������ ���� (����������) ������� ��� ������������ ����
		auto nextStep = alternatives.begin(); // ��������� �� ��������� �������

		for (auto it = alternatives.begin(); it != alternatives.end(); it++) // ���� ���������� ����������� ����� ������ 
		{
			if (it->waylenght < minwaylength)
			{
					minwaylength = it->waylenght;
			}
		}

		for (auto it = alternatives.begin(); it != alternatives.end(); it++) // ���� ���������� ������������ ������� ���� ����� ������� � ����������� ������ 			{
		{
			if ((it->waylenght == minwaylength) && (it->stepWayPair.size() > maxchain))
			{
				maxchain = it->stepWayPair.size();
			}
		}

		for (auto it = alternatives.begin(); it != alternatives.end(); it++) // ���� ���������� ������� ������ (� ����������� ������ � ��� �� ������������ �����)
		{
			if ((ourStep.waylenght == it->waylenght) && (maxchain == it->stepWayPair.size()))
			{
				nextStep = it; 
				ourStep.SwapActive(*nextStep); // ������ ��� �������� ����
				break; // �� ���� ��� �� �����, ����� �� ������� � ���������� ������ � ������ ������ ������� ����� ������� ��� �����������
			}
		}

	}

	void AddNextCityLeft()
	{

	}

	void AddNextCityRight(FrizeStep rightFrizeNotActive) // �������� ��� �������� ������ �������� ������� FrizeStep (�����������)
	{
		
	}

		void step1(Matrix& originalMatrix)// ������� ����� �������?
		{
			firstRedaction(originalMatrix);
			FrizeStep firstFrize; 
			firstFrize.matrixStepCity = originalMatrix; firstFrize.active = true;
			std::map<int, int> wayPair;
			std::list<std::pair<int, int>> filtrWayPair;// ����� ��� ������� ����������
			std::cout << "\n------------------------�������� ������------------------------\n\n";

			while (originalMatrix.matrix.size() != 0)
			{
				maxi = 0;
				maxj = 0;
				zerosPower(originalMatrix);
				Matrix copyMatrix1(originalMatrix); // ������� �������, ����� ��� ��������� �������� ������ (��� ������������� ������� leftway)  ����� �� ����� �������
				Matrix copyMatrix2(originalMatrix); // ������� �������, ����� ��� ��������� �������� ������ (��� ������������� ������� rightway) ����� �� ����� �������

				if (leftway(copyMatrix1) < BnB::rightway(copyMatrix2)) // ����� ����
				{
					AddNextCityRight(firstFrize);
					leftway(originalMatrix);
				}
				else // ������ ����
				{
					realRightWay(originalMatrix, wayPair, filtrWayPair);

					RightOrEnd(originalMatrix); // ��� ������� ������� �������, ��� ���� ������, ����� ���������� ���� ����� ������� ����� ������� ����
				}
			}

			//"��������� ���� �����" 
			joinPairIntoLastWay(wayPair);
			wayAndLong(originalMatrix); // ���� � ��� ����� 
		}

		/*
		//AnalizNextStep()
		std::cout << "����� ������ ���� ������� ���������:\n";
		originalMatrix.printM();
		//std::cout << "�� ������ ������ ����� ����� ���� = " << originalMatrix.allbound << std::endl;
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


	