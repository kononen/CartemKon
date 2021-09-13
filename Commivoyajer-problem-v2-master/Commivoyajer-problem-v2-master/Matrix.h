#pragma once

#include <vector>

class Matrix
{
	public:
		std::vector<std::vector<int>> matrix;
		std::vector<int> horzHeading;
		std::vector<int> vertHeading;
		int allbound = 0;
		//std::vector<int> horzMin;
		//std::vector<int> vertMin;

		Matrix();

		Matrix( int min, int max, int dim );

		Matrix(const Matrix& otherM);// ����������� �����������

		void printM();

		int minInRow(const int& rowNum);
		int minInCol(const int& colNum);
		
		int fsummaVertMin(); // ���� void, ��� ��� � ��� ����� ��������� �� ������� ��������� � ��������� ���� ������ (� ���� ����, ��� ����� �������������� ������� lawBound ������� ����������)
		int fsummaHorzMin();
		int lowerBound(); // �������, ��������, ����� �����������, ����� lawBound ��� ���� void / ����� ���� ���������� ������� ���� ������ All 

		void rowReduction(const int& rowNum, const int& reductionNumber);
		void colReduction(const int& colNum, const int& reductionNumber);

		void globalRowReduction();
		void globalColReduction();

		void deleteRow(const int& rowNum);
		void deleteCol(const int& colNum);

	private:

		int chVertMin = 0;
		int chHorzMin = 0;
		void catchBlock_(int& errorCode);
};

