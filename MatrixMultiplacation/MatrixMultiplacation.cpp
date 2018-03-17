// MatrixMultiplacation.cpp: определяет точку входа для консольного приложения.
//

#define RowC 16
#define ColumnC 16

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "cmath"

void printMatrix(int **matA, int row, int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			std::cout << matA[i][j] << "	";
		}
		std::cout << std::endl;
	}
}

//умножение чисел в части в матрице
int **PartMatrixMult(int **partMatA, int **partMatB, int N) {
	int **partMatC = new int *[N];
	for (int i = 0; i < N; i++) {
		partMatC[i] = new int[N];
		for (int j = 0; j < N; j++) {
			partMatC[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int iMatA = 0; iMatA < N; iMatA++) {
				partMatC[i][j] += partMatA[i][iMatA] * partMatB[iMatA][j];
			}
		}
	}
	return partMatC;
}


int **MatrixMult(int **mA, int **mB, int N) {
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
	int **matC = new int* [N];
	for (int i = 0; i < N; i++) {
		matC[i] = new int [N];
	}
	//номер блока в матрице А
	int numberRowBlockA = 0;
	int numberColumnBlockA = 0;
	//номер блока в матрице B
	int numberRowBlockB = 0;
	int numberColumnBlockB = 0;
	int number;
	int iteration = 0;
	while (numberRowBlockA < nRowBlocksA) { ///проверить количество итераций!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		numberColumnBlockB = 0;
		//блок, считающий одну строку в матрице С
		while (numberColumnBlockB < nColumnBlocksB)
		{
			numberColumnBlockA = 0;
			numberRowBlockB = 0;

			//блок, считающий одну ячейку 
			while (numberColumnBlockA < nColumnBlocksA)
			{
				int **partMatA = new int*[N / nRowBlocksA];
				int **partMatB = new int*[N / nRowBlocksB];
				for (int i = 0; i < N / nRowBlocksA; i++) {
					partMatA[i] = new int[N / nColumnBlocksA];
				}
				for (int i = 0; i < N / nRowBlocksB; i++) {
					partMatB[i] = new int[N / nColumnBlocksB];
				}
				for (int i = 0; i < N / nRowBlocksA; i++) {
					for (int j = 0; j < N / nColumnBlocksA; j++) {
						partMatA[i][j] = matA[i + numberRowBlockA * (N / nRowBlocksA)][j + numberColumnBlockA * (N / nColumnBlocksA)];
					}
				}
				//std::cout << "PartMatrix A[" << numberRowBlockA << "][" << numberColumnBlockA << "] : " << std::endl;
				//printMatrix(partMatA, N / nRowBlocksA, N / nColumnBlocksA);
				//std::cout << std::endl;
				for (int i = 0; i < N / nRowBlocksB; i++) {
					for (int j = 0; j < N / nColumnBlocksB; j++) {
						partMatB[i][j] = matB[i + numberRowBlockB * (N / nRowBlocksB)][j + numberColumnBlockB * (N / nColumnBlocksB)];
					}
				}
				//std::cout << "PartMatrix B[" << numberRowBlockB << "][" << numberColumnBlockB << "] : " << std::endl;
				//printMatrix(partMatB, N / nRowBlocksB, N / nColumnBlocksB);
				//std::cout << std::endl;
				int **partMatC = PartMatrixMult(partMatA, partMatB, N / nRowBlocksA);
				//std::cout << "PartMatrix C[" << numberRowBlockA << "][" << numberColumnBlockB << "] : " << std::endl;
				//printMatrix(partMatC, N / nRowBlocksA, N / nColumnBlocksB);
				//std::cout << std::endl;
				for (int i = 0; i < N / nRowBlocksA; i++) {
					for (int j = 0; j < N / nColumnBlocksB; j++) {
						matC[i + numberRowBlockA * (N / nRowBlocksA)][j + numberColumnBlockB * (N / nRowBlocksA)] = partMatC[i][j];
					}
				}
				numberColumnBlockA++;
				numberRowBlockB++;

				for (int i = 0; i < N / nRowBlocksA; i++) {
					delete[] partMatA[i];
				}
				for (int i = 0; i < N / nRowBlocksB; i++) {
					delete[] partMatB[i];
				}
				for (int i = 0; i < N / nRowBlocksA; i++) {
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
	int N;
	std::cout << "Input N - rows and columns for matrix A : " << std::endl;
	
	std::cin >> N;
	if (N < 2)std::cout << "Введите данные корректно(количество столбцов матрицы А должно совпадать с количеством строк матрицы B" << std::endl;
	else
	{
		std::cout << N << std::endl;
		int **matA = new int* [N];
		int **matB = new int* [N];
		for (int i = 0; i < N; i++) {
			matA[i] = new int [N];
			matB[i] = new int [N];
		}
		std::cout << " Matrix A:" << std::endl;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matA[i][j] = i + 1;
				//std::cout << matA << "	";
			}
			//std::cout << std::endl;
		}
		printMatrix(matA, N, N);
		std::cout << std::endl;
		std::cout << std::endl;		
		std::cout << " Matrix B:" << std::endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matB[i][j] = i + 1;
				//std::cout << matB << "	";
			}
			//std::cout << std::endl;
		}
		printMatrix(matB, N, N);
		std::cout << std::endl;
		std::cout << std::endl;

		//int **matC = new int*[N];
		//for (int i = 0; i < N; i++) {
		//	matC[i] = new int[N];
		//}
		//matC = MatrixMult(matA, matB, N);
		int **matC = MatrixMult(matA, matB, N);
		std::cout << "Matrix C:" << std::endl;
		printMatrix(matC, N, N);
	}	
    return 0;
}

