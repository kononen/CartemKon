#pragma once

#include <vector>

class Matrix
{
	public:
		std::vector<std::vector<int>> matrix; // основная матрица
		//std::vector<std::vector<int>> baseDataMatrix; // матрица с исходными данными, которая не меняется. Нужна для сравнимания нулей с равной суммой констант приведения
		std::vector<int> horzHeading; // вектор с сохранёнными с начала индексами строк, которые хранят в себе порядок этих строк
		std::vector<int> vertHeading; // --\\-- индексами столбцов --\\--
		int allbound = 0;// длина всего пути

		Matrix();// конструктор по умолчанию

		Matrix( int min, int max, int dim ); // конструктор инициализации

		Matrix(const Matrix& otherM);// конструктор копирования

		void operator=(const Matrix& otherM); // оператор равенства

		//void equalityFirstData(); // в baseDataMatrix присваиваем значение matrix з

		void printM(); // выводим матрицу

		int minInRow(const int& rowNum);// находим минимум по строке
		int minInCol(const int& colNum);// находим минимум по столбцу
		
		int fsummaVertMin(); // возвращает сумму вертикальных минимумов
		int fsummaHorzMin(); // возвращает сумму горизонтальных минимумов 
		int lowerBound(); // сумма минимумов по строкам и по столбцам

		void rowReduction(const int& rowNum, const int& reductionNumber); // вычитаем из всех элементов строки число rowNum 
		void colReduction(const int& colNum, const int& reductionNumber); // вычитаем из всех элементов столбца число colNum

		void globalRowReduction(); // вычитаем из всех строк минимумы по тем строкам 
		void globalColReduction(); // вычитаем из всех столбцов минимумы по тем столбцам

		void deleteRow(const int& rowNum); // удаляем строку
		void deleteCol(const int& colNum); // удаляем столбец

	private:

		int chVertMin = 0; // сумма минимумов по строкам
		int chHorzMin = 0; // сумма минимумов по столбцам
		void catchBlock_(int& errorCode); // ловит исключения
};

