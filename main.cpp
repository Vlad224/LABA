#include "Prog1.h"
#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");
	cout << "������";
	Prog1::Matrix* matr = nullptr;
	Prog1::Matrix* new_matr = nullptr;
	int m = 0;
	int n = 0;
	const char* pr = "";
	do {
		cout << pr << endl;
		pr = "������ �������� ������������ ������(��������� ������� 3)";
		cout << "������� ���������� �����" << endl;
		if (Prog1::getNum(m) < 0) // ���������� ������ ����� ��� ����� �����
		{
			cout << "������������ ������" << endl;
			return 1;
		}
		cout << "������� ���������� ��������" << endl;
		if (Prog1::getNum(n) < 0) // ���������� ������ ����� ��� ����� �����
		{
			cout << "������������ ������" << endl;
			return 1;
		}
	} while (n<1||m<1||m*n<3);
	matr=Prog1::input(m, n);
	if (!matr) {
		cout << "������������ ������" << endl;
		return 1;
	}
	if (m > 1)
	{
		Prog1::output("�������� �������: ", matr, n, m);
		new_matr = Prog1::Copy(matr);
		if (!new_matr) {
			cout << "������ �������� ������" << endl;
			return 1;
		}
		new_matr = Prog1::SwapLine(new_matr, 0, n,Prog1::Find);
		new_matr = Prog1::SwapLine(new_matr, m - 1, n,Prog1::Find);
		Prog1::output("����� �������: ", new_matr, n, m);
	}
	else {
		cout << "��� ��� m=1 � ��� �������� ������� � ���� �����" << endl;
		Prog1::output("�������� �������: ", matr, n, m);
	}
	Prog1::erase(new_matr);
	Prog1::erase(matr);
	return 0;

}