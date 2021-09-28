#include "Matrix.h"

#include <ctime>
#include <iostream>
#include "Globals.h"


Matrix::Matrix():Matrix(Globals::defaultGenerationMin, Globals::defaultGenerationMax, Globals::defaultSize)
{
}

Matrix::Matrix(int min, int max, int dim)
{
	std::srand(time(NULL));

	std::vector<int> matrixRow;
	for (int i = 0; i < dim; i++)
	{
		horzHeading.push_back(i);
		vertHeading.push_back(i);

		for (int j = 0; j < dim; j++)
		{
			if (i == j)
			{
				matrixRow.push_back(-1);
			}
			else
			{
				matrixRow.push_back(rand() % (max - min + 1) + min);
			}
		}
		matrix.push_back(matrixRow);
		matrixRow.clear();
	}
	
}

Matrix::Matrix(const Matrix& otherM)
{
	std::vector<int> matrixRow;
	for (int i = 0; i < otherM.matrix.size(); i++)
	{
		this->horzHeading.push_back(otherM.horzHeading[i]);
		this->vertHeading.push_back(otherM.vertHeading[i]);

		for (int j = 0; j < otherM.matrix.size(); j++)
		{
			matrixRow.push_back(otherM.matrix[i][j]);
		}
		matrix.push_back(matrixRow);
		matrixRow.clear();
	}
} 

//void Matrix::equalityFirstData()
//{
//	std::vector<int> matrixRow;
//	for (int i = 0; i < this->matrix.size(); i++)
//	{
//		this->horzHeading.push_back(i);
//		this->vertHeading.push_back(i);
//
//		for (int j = 0; j < this->matrix.size(); j++)
//		{
//			matrixRow.push_back(this->matrix[i][j]);
//		}
//		this->baseDataMatrix.push_back(matrixRow);
//		matrixRow.clear();
//	}
//}

void Matrix::printM()
{
	//std::cout << std::endl;
	//std::cout.setf(std::ios::left);
	//for (int k = 0; k < matrix.size(); k++)
	//{
	//	std::cout << "==========";
	//}
	//std::cout << std::endl;
	//for (int k = 0; k < matrix.size(); k++)
	//{
	//	std::cout << "\t   " << horzHeading[k];
	//}
	//std::cout << std::endl;
	//for (int k = 0; k < matrix.size(); k++)
	//{
	//	std::cout << "==========";
	//}
	//std::cout << std::endl;

	//for (int i = 0; i < horzHeading.size(); i++)
	//{
	//	std::cout << vertHeading[i];
	//	std::cout.setf(std::ios::right);
	//	std::cout << " ||";
	//	for (int j = 0; j < vertHeading.size(); j++)
	//	{
	//		std::cout.setf(std::ios::right);
	//		std::cout.width(8);
	//		std::cout << matrix[i][j];
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout.setf(std::ios::left);
}

int Matrix::minInRow(const int& rowNum)
{
	try
	{
		if ((rowNum > matrix.size()) or (rowNum < 0))
		{
			throw(100);
		}
		bool positiveFound = false;
		int j = 0;
		int min = -1;// замен€ем на -1, как на самый минимально возможный элемент
		// находим первое положительное число
		while (!positiveFound && (j < matrix.size())) // добавил условие: && (j < matrix.size()), так как в случае, если все элементы строки отрицательные, то можем бесконечно увеличивать j
		{	
			if (matrix[rowNum][j] >= 0)
			{
				positiveFound = true;
				min = matrix[rowNum][j];
				break;
			}
				j++;
		}

		for (auto& number : matrix[rowNum])
		{
			if (number < min && number >= 0)
			{
				min = number;
			}
		}

		if (min == -1) { min = 0; };// в случае, если все €чейки строки rowNum матрицы отрицательные
		return min;
	}
	catch(int errorCode)
	{
		catchBlock_(errorCode);
	}
}

int Matrix::minInCol(const int& colNum)
{
	try
	{
		if ((colNum > matrix.size()) or (colNum < 0))
		{
			throw(100);
		}
		int positivei = 0;
		bool positiveFound = false;
		int min = -1;
		// находим первое положительное число
		while (!positiveFound && (positivei < matrix.size())) // добавил условие: && (i < matrix.size()) так как в случае, если все элементы столбца = -1, то то можем бесконечно увеличивать i
		{
			if (matrix[positivei][colNum] >= 0)
			{
				positiveFound = true;
				min = matrix[positivei][colNum];
				break;
			}
			positivei++;
		}

		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[i][colNum] < min && matrix[i][colNum] >= 0)
			{
				min = matrix[i][colNum];
			}
		}

		if (min == -1) { min = 0; };// в случае, если все €чейки столбца матрицы отрицательные

		return min;
	}
	catch (int errorCode)
	{
		catchBlock_(errorCode);
	}
}

int Matrix::fsummaVertMin() // вызываетс€ перед globalRowReduction
{
	this->chVertMin = 0; // инициализируем нулЄм дл€ того, чтобы сбрасывать значени€ после ветвлени€
	for (int i = 0; i < matrix.size(); i++)
	{
		this->chVertMin += minInRow(i);
	}
	return chVertMin;
}

int Matrix::fsummaHorzMin() // вызываетс€ перед globalColReduction
{
	this->chHorzMin = 0;
	for (int i = 0; i < matrix.size(); i++)
	{
		this->chHorzMin += minInCol(i);
	}
	return chHorzMin;
}

void Matrix::rowReduction(const int& rowNum, const int& reductionNumber)
{
	try
	{
		if ((rowNum > matrix.size()) or (rowNum < 0))
		{
			throw(100);
		}

		for (auto& number : matrix[rowNum])
		{
			if (number != -1)
			{
				number -= reductionNumber;
			}
		}

	}
	catch (int errorCode)
	{
		catchBlock_(errorCode);
	}
}

void Matrix::colReduction(const int& colNum, const int& reductionNumber)
{
	try
	{
		if ((colNum > matrix.size()) or (colNum < 0))
		{
			throw(100);
		}

		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[i][colNum] != -1)
			{
				matrix[i][colNum] -= reductionNumber;
			}
		}

	}
	catch (int errorCode)
	{
		catchBlock_(errorCode);
	}
}

void Matrix::globalRowReduction()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		this->rowReduction(i, this->minInRow(i));
	}
}

void Matrix::globalColReduction()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		this->colReduction(i, this->minInCol(i));
	}
}

int Matrix::lowerBound()
{
	return (chHorzMin + chVertMin);
}

void Matrix::deleteRow(const int& rowNum)
{
	try
	{
		if ((rowNum > matrix.size()) or (rowNum < 0))
		{
			throw(100);
		}
		matrix[rowNum].clear();
		matrix.erase(matrix.begin() + rowNum);
		vertHeading.erase(vertHeading.begin() + rowNum);// удал€ем индекс строки
	}
	catch (int errorCode)
	{
		catchBlock_(errorCode);
	}
}

void Matrix::deleteCol(const int& colNum)
{
	try
	{
		if ((colNum > matrix.size()) or (colNum < 0))
		{
			throw(100);
		}

		for (int i = 0; i < matrix.size(); i++)
		{
			matrix[i].erase(matrix[i].begin() + colNum);
		}

		horzHeading.erase(horzHeading.begin() + colNum);// удал€ем индекс колонки 
	}
	catch (int errorCode)
	{
		catchBlock_(errorCode);
	}
}

void Matrix::catchBlock_(int& errorCode)
{
	if (errorCode == 100)
	{
		std::cout << "index is out of matrix array range";
	}
	exit(errorCode);
}
