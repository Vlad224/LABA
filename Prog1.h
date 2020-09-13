#pragma once
#include<iostream>
namespace Prog1{
	struct Matrix{
		Matrix* line;
		Matrix* next;
		double digit;
		int i;
		int j;
	};
	// шаблон функций ввода одного значения
	template <class T>
	int getNum(T& a)
	{
		std::cin >> a;
		if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
			return -1;
		return 1;
	}
	Matrix* input(int,int); // ввод матрицыл
	Matrix* Find(Matrix*& matr, int a, int n,int& p);//Поиск максимальных строк по отрицат и положит
	Matrix* SwapLine(Matrix*, int, int,Matrix* (*f)(Matrix*&,int,int,int&));//свап местами строчки
	void output(const char* msg, Matrix* a,int m, int n); // вывод матрицы
	Matrix* erase(Matrix*& a); // освобождение занятой памяти
	Matrix* Copy(Matrix*& a);
}
