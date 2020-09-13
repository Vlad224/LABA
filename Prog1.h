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
	// ������ ������� ����� ������ ��������
	template <class T>
	int getNum(T& a)
	{
		std::cin >> a;
		if (!std::cin.good())	// ���������� ������ ����� ��� ����� �����
			return -1;
		return 1;
	}
	Matrix* input(int,int); // ���� ��������
	Matrix* Find(Matrix*& matr, int a, int n,int& p);//����� ������������ ����� �� ������� � �������
	Matrix* SwapLine(Matrix*, int, int,Matrix* (*f)(Matrix*&,int,int,int&));//���� ������� �������
	void output(const char* msg, Matrix* a,int m, int n); // ����� �������
	Matrix* erase(Matrix*& a); // ������������ ������� ������
	Matrix* Copy(Matrix*& a);
}
