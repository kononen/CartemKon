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
	/*for (int i = 0; i < otherM.matrix.size(); i++)
	{
		for (int j = 0; j < otherM.matrix.size(); j++)
		{
			this->matrix[i][j] = otherM.matrix[i][j];
		}
	}*/
	std::vector<int> matrixRow;
	for (int i = 0; i < otherM.matrix.size(); i++)
	{
		this->horzHeading.push_back(i);
		this->vertHeading.push_back(i);

		for (int j = 0; j < otherM.matrix.size(); j++)
		{
			matrixRow.push_back(otherM.matrix[i][j]);
		}
		matrix.push_back(matrixRow);
		matrixRow.clear();
	}
}

void Matrix::printM()
{
	std::cout << std::endl;
	std::cout.setf(std::ios::left);
	for (int k = 0; k < matrix.size(); k++)
	{
		std::cout << "=========";
	}
	std::cout << std::endl;
	for (int k = 0; k < matrix.size(); k++)
	{
		std::cout << "\t   " << horzHeading[k];
	}
	std::cout << std::endl;
	for (int k = 0; k < matrix.size(); k++)
	{
		std::cout << "=========";
	}
	std::cout << std::endl;

	for (int i = 0; i < horzHeading.size(); i++)
	{
		std::cout << vertHeading[i];
		std::cout.setf(std::ios::right);
		std::cout << " ||";
		for (int j = 0; j < vertHeading.size(); j++)
		{
			std::cout.setf(std::ios::right);
			std::cout.width(8);
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout.setf(std::ios::left);
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
		int i = 0;
		int j = 0;
		int min = -1;// = INT_MAX;// не понимаю логики, зачем минимум = -1 ? 
		while (!positiveFound)
		{
			while (!positiveFound)
			{	
				if (matrix[i][j] >= 0)
				{
					positiveFound = true;
					min = matrix[i][j];
				}
				j++;
			}
			i++;
		}

		for (auto& number : matrix[rowNum])
		{
			//if ( number < min && number != -1)
			if (number < min && number >= 0)
			{
				min = number;
			}
		}

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

		int min = INT_MAX;// не понимаю логики, зачем минимум = -1 ? 
		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[i][colNum] < min && matrix[i][colNum] != -1)
			{
				min = matrix[i][colNum];
			}
		}

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
		//horzMin.push_back(this->minInRow(i)); // похоже на костыль, хотелось бы от него избавитьс€ в будущем. Ќужен дл€ запоминани€ столбца минимумов.
		this->rowReduction(i, this->minInRow(i));
	}
}

void Matrix::globalColReduction()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		//vertMin.push_back(this->minInCol(i)); // похоже на костыль, хотелось бы от него избавитьс€ в будущем. Ќужен дл€ запоминани€ строки минимумов.
		this->colReduction(i, this->minInCol(i));
	}
}

int Matrix::lowerBound()
{
	return chHorzMin + chVertMin;
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
		vertHeading.erase(vertHeading.begin() + rowNum);
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

		horzHeading.erase(horzHeading.begin() + colNum);
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
