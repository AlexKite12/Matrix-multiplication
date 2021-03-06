// MatrixMultiplacation.cpp: определяет точку входа для консольного приложения.
//

#define RowC 16
#define ColumnC 16

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "cmath"
#include "windows.h"
#include <chrono>

unsigned __int64 tick() {
	return (__rdtsc());
}

void printMatrix(int **matA, int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			std::cout << matA[i][j] << "	";
		}
		std::cout << std::endl;
	}
}

//Умножение чисел в части в матрице
//
//	блоки произведения 2ух матриц одинаковы 
int **PartMatrixMult(int **partMatA, int **partMatB, int rows, int columns, int matRows) {
	int **partMatC = new int * [rows];
	for (int i = 0; i < rows; i++) {
		partMatC[i] = new int [columns];
		for (int j = 0; j < columns; j++) {
			partMatC[i][j] = 0;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			for (int iMatA = 0; iMatA < matRows; iMatA++) {
				partMatC[i][j] += partMatA[i][iMatA] * partMatB[iMatA][j];
			}
		}
	}
	//std::cout << std::endl;
	//printMatrix(partMatC, rows, columns);
	return partMatC;
}


int **MatrixMult(int **mA, int **mB, int rowsA, int columnsA, int rowsB, int columnsB) {
	//количество блоков в строках и в столбцах  в матрице А
	int nRowBlocksA = 4;
	int nColumnBlocksA= 4;
	//количество блоков в строках и в столбцах  в матрице B
	int nRowBlocksB = 4;
	int nColumnBlocksB = nRowBlocksA;
	//хз как создать блоки основываясь на количестве чисел в строке/столбце
	/*int k = 0;
	while (k == 0)
	{
		k = 0;

	}
	while (rowMatrixA % nRowBlocksA != 0)
	{
		nRowBlocksA++;
	}
	while (columnMatrixA % nColumnBlocksA != 0)
	{
		nColumnBlocksA++;
	}*/
	int ** const matA = mA;
	int ** const matB = mB;
	int **matC = new int* [rowsA];
	for (int i = 0; i < rowsA; i++) {
		matC[i] = new int [columnsB];
		for (int j = 0; j < columnsB; j++) {
			matC[i][j] = 0;
		}
	}

	//номер блока в матрице А
	int numberRowBlockA = 0;
	int numberColumnBlockA = 0;
	//номер блока в матрице B
	int numberRowBlockB = 0;
	int numberColumnBlockB = 0;
	int number;
	int iteration = 0;
	while (numberRowBlockA < nRowBlocksA) {
		numberColumnBlockB = 0;

		//блок, считающий одну строку в матрице С
		while (numberColumnBlockB < nColumnBlocksB)
		{
			numberColumnBlockA = 0;
			numberRowBlockB = 0;

			//блок, считающий одну ячейку 
			while (numberColumnBlockA < nColumnBlocksA)
			{
				int **partMatA = new int*[rowsA / nRowBlocksA];
				int **partMatB = new int*[rowsB / nRowBlocksB];
				for (int i = 0; i < rowsA / nRowBlocksA; i++) {
					partMatA[i] = new int[columnsA / nColumnBlocksA];
				}
				for (int i = 0; i < rowsB / nRowBlocksB; i++) {
					partMatB[i] = new int[columnsB / nColumnBlocksB];
				}
				for (int i = 0; i < rowsA / nRowBlocksA; i++) {
					for (int j = 0; j < columnsA / nColumnBlocksA; j++) {
						partMatA[i][j] = matA[i + numberRowBlockA * (rowsA / nRowBlocksA)][j + numberColumnBlockA * (columnsA / nColumnBlocksA)];
					}
				}
				//std::cout << "PartMatrix A[" << numberRowBlockA << "][" << numberColumnBlockA << "] : " << std::endl;
				//printMatrix(partMatA, rowsA / nRowBlocksA, columnsA / nColumnBlocksA);
				//std::cout << std::endl;
				for (int i = 0; i < rowsB / nRowBlocksB; i++) {
					for (int j = 0; j < columnsB / nColumnBlocksB; j++) {
						partMatB[i][j] = matB[i + numberRowBlockB * (rowsB / nRowBlocksB)][j + numberColumnBlockB * (columnsB / nColumnBlocksB)];
					}
				}
				//std::cout << "PartMatrix B[" << numberRowBlockB << "][" << numberColumnBlockB << "] : " << std::endl;
				//printMatrix(partMatB, rowsB / nRowBlocksB, columnsB / nColumnBlocksB);
				//std::cout << std::endl;
				int **partMatC = PartMatrixMult(partMatA, partMatB, rowsA / nRowBlocksA, columnsB/ nColumnBlocksB, columnsA/nColumnBlocksA);
				//std::cout << "PartMatrix C[" << numberRowBlockA << "][" << numberColumnBlockB << "] : " << std::endl;
				//printMatrix(partMatC, rowsA / nRowBlocksA, columnsB / nColumnBlocksB);
				//std::cout << std::endl;
				for (int i = 0; i < rowsA / nRowBlocksA; i++) {
					for (int j = 0; j < columnsB / nColumnBlocksB; j++) {
						matC[i + numberRowBlockA * (rowsA / nRowBlocksA)][j + numberColumnBlockB * (columnsB / nColumnBlocksB)] += partMatC[i][j];
					}
				}
				numberColumnBlockA++;
				numberRowBlockB++;

				for (int i = 0; i < rowsA / nRowBlocksA; i++) {
					delete[] partMatA[i];
				}
				for (int i = 0; i < rowsB / nRowBlocksB; i++) {
					delete[] partMatB[i];
				}
				for (int i = 0; i < rowsA / nRowBlocksA; i++) {
					delete[] partMatC[i];
				}
			}

			numberColumnBlockB++;
		}
			
		numberRowBlockA++;
	}
	return matC;
}


int main()
{
	int rowMatrix, columnMatrix;
	int RowsA, ColumnsA;
	std::cout << "Input N and M - rows and columns for matrix A : " << std::endl;	
	std::cin >> RowsA;
	std::cin >> ColumnsA;
	int RowsB, ColumnsB;
	std::cout << "Input N and M - rows and columns for matrix B : " << std::endl;
	std::cin >> RowsB;
	std::cin >> ColumnsB;
	if ((RowsA < 2) || (ColumnsA < 2) || ((RowsB < 2) || (ColumnsB < 2)) || (ColumnsA != RowsB))std::cout << "Введите данные корректно(количество столбцов матрицы А должно совпадать с количеством строк матрицы B" << std::endl;
	else
	{
		int **matA = new int* [RowsA];
		int **matB = new int* [RowsB];
		for (int i = 0; i < RowsA; i++) {
			matA[i] = new int [ColumnsA];
			
		}
		for (int i = 0; i < RowsB; i++) {
			matB[i] = new int[ColumnsB];
		}
		std::cout << " Matrix A:" << std::endl;
		
		for (int i = 0; i < RowsA; i++) {
			for (int j = 0; j < ColumnsA; j++) {
				matA[i][j] = 1;
			}
		}
		printMatrix(matA, RowsA, ColumnsA);
		std::cout << std::endl;
		std::cout << std::endl;		
		std::cout << " Matrix B:" << std::endl;
		for (int i = 0; i < RowsB; i++) {
			for (int j = 0; j < ColumnsB; j++) {
				matB[i][j] = 2;
			}
		}
		printMatrix(matB, RowsB, ColumnsB);
		std::cout << std::endl;
		std::cout << std::endl;

		//unsigned __int64 a, b;
		auto begin = std::chrono::steady_clock::now();
		//a = tick();
		// проверяемый код
		int **matC = MatrixMult(matA, matB, RowsA, ColumnsA, RowsB, ColumnsB);
		auto end = std::chrono::steady_clock::now();

		auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		//b = tick();
		 // время 
		std::cout << "Matrix C:" << std::endl;
		printMatrix(matC, RowsA, ColumnsB);
		std::cout << std::endl;
		std::cout << "Time is: " << elapsed_ms.count() << " nanosec" << std::endl;

		//std::cout << "Time is:" << a - b << std::endl;
	}	
    return 0;
}

