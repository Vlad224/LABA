#include <iostream>
#include "Prog1.h"
namespace Prog1 {
	Matrix* erase(Matrix* &matr) {
		Matrix* ptr = nullptr;
		Matrix* del = nullptr;
		while (matr != nullptr)
		{
			ptr = matr;
			matr = matr->next;
			while (ptr != nullptr)
			{
				del = ptr;
				ptr = ptr->line;
				delete del;
			}
		}
		return nullptr;
	}
	Matrix* input(int m, int n) {
		Matrix* mtr = nullptr;
		Matrix* ptr = nullptr;
		Matrix* ptr_find = nullptr;
		const char* pr = "";
		int k;
		do {
			std::cout << pr << std::endl;
			std::cout << "Введите сколько хотите добавить элементов: --> ";
			pr = "Вы ошиблись повторите снова! Возможно вы вели слишком много элементов";
			if (getNum(k) < 0) // обнаружена ошибка ввода или конец файла
				return nullptr;
		} while ((k<1)||(k>m*n/2));
		for (int i = 0; i < k; i++) 
		{
			try {
				ptr = new Matrix;
				std::cout << "Элемент " << i;
			}
			catch (std::bad_alloc & ba)
			{
				std::cout << "------ Слишком много строк в матрице: " << ba.what() << std::endl;
				mtr = erase(mtr);
				return nullptr;
			}
			pr = "";
			do
			{
				std::cout << pr << std::endl;
				pr = "Ошибка. Выход за матрицу";
				std::cout << "Введите номер строки в которую хотите добавить элемент(От 0 до " << m-1 <<" )"<<std::endl;
				if (getNum(ptr->i) < 0) // обнаружена ошибка ввода или конец файла
				{
					mtr = erase(mtr);
					return nullptr;
				}
				std::cout << "Введите номер столбца в который хотите добавить элемент(От 0 до " << n - 1 << " )" << std::endl;
				if (getNum(ptr->j) < 0) // обнаружена ошибка ввода или конец файла
				{
					mtr = erase(mtr);
					return nullptr;
				}
			} while ((ptr->i >= m) || (ptr->j >= n) || (ptr->i <0) || (ptr->j < 0));
			pr = "";
			do {
				std::cout << pr << std::endl;
				pr = "Ошибка. Выход за матрицу";
				std::cout << "Введите сам элемент" << std::endl;
				if (getNum(ptr->digit) < 0) // обнаружена ошибка ввода или конец файла
				{
					mtr = erase(mtr);
					return nullptr;
				}
			} while (ptr->digit == 0);
			ptr->line = nullptr;
			ptr->next = nullptr;
			if (mtr == nullptr)//смотрим первый элемент
				mtr = ptr;
			else 
			{
				if ((mtr->i > ptr->i)||(mtr->i==ptr->i)) {    //продолжаем анализировать первый элемент
					if (mtr->i > ptr->i) {
						ptr->next = mtr;
						mtr = ptr;
					}
					else {
						if (mtr->j == ptr->j)
							std::cout << "Введеный элемент уже существует" << std::endl;
						else {
							if (mtr->j > ptr->j) {
								ptr->line = mtr;
								ptr->next = mtr->next;
								mtr = ptr;
							}
							else {
								ptr_find = mtr;
								while ((ptr_find->line != nullptr) && (ptr_find->line->j < ptr->j))
									ptr_find = ptr_find->line;
								ptr->line = ptr_find->line;
								ptr_find->line = ptr;
							}
						}
					}
				}
				else
				{
						ptr_find = mtr;
						while ((ptr_find->next != nullptr) && (ptr_find->next->i < ptr->i))
							ptr_find = ptr_find->next;
						if (ptr_find->next == nullptr)
							ptr_find->next = ptr;
						else {
							if (ptr_find->next->i == ptr->i)
							{
								if (ptr_find->next->j > ptr->j)
								{
									ptr->line = ptr_find->next;
									ptr->next = ptr_find->next->next;
									ptr_find->next = ptr;
								}
								else {
									ptr_find = ptr_find->next;
									while ((ptr_find->line != nullptr) && (ptr_find->line->j < ptr->j))
										ptr_find = ptr_find->line;
									if ((ptr_find->line != nullptr) &&(ptr_find->line->j == ptr->j))
										std::cout << "Введеный элемент уже существует в матрице" << std::endl;
									else {
										ptr->line = ptr_find->line;
										ptr_find->line = ptr;
									}
								}
							}
							else {
								ptr->next = ptr_find->next;
								ptr_find->next = ptr;
							}
						}
				}
			}
		}
		return mtr;
	}
	void output(const char* msg, Matrix* a,int n,int m) { // вывод матрицы
		std::cout << msg << std::endl;
		Matrix* ptr = nullptr;
		int j=0;
		int helping = 0;
		if (n * m > 200) {
			while (a!= nullptr) {
				ptr = a;
				while (ptr != nullptr) {
					std::cout << "Строка: "<< ptr->i << "Столбец: "<< ptr->j<< "Элемент: "<< ptr->digit<<std::endl;
					ptr = ptr->line;
				}
				std::cout << "--------------------------------------------------------------------" << std::endl;
				a = a->next;
			}
		}
		else
		{
			for(int i=0;i<m;i++){
				if ((a!=nullptr)&&(a->i == i)){
					ptr = a;
					j = 0;
					helping = 0;
					while (ptr != nullptr) {
						for (int k = 0; k < ptr->j - j-helping; k++)
							std::cout << 0 << " ";
						j = ptr->j;
						helping = 1;
						std::cout << ptr->digit << " ";
						ptr = ptr->line;
					}
					for(int k=0;k<(n-1)-j;k++)
						std::cout << 0 << " ";
					std::cout << std::endl;
					a = a->next;
				}
				else {
					for (int k = 0; k < n; k++)
						std::cout << 0 << " ";
					std::cout << std::endl;
				}
			}
		}
	}
	Matrix* Copy(Matrix* &old_matr) {
		Matrix* new_matr = nullptr;//новая матрица
		Matrix* new_ptr = nullptr;//новый элемнт для новой матрицы
		Matrix* new_ptr_matr = nullptr;//переход по столбцам в новой матрице
		Matrix* new_ptr_line = nullptr;//
		Matrix* ptr_line = nullptr;//переход по строке
		Matrix* ptr = old_matr;//переход по столбцам
		while (ptr!=nullptr) {
			ptr_line = ptr;
			while (ptr_line != nullptr) {

				try {
					new_ptr_line = new_ptr;
					new_ptr = new Matrix;
				}
				catch (std::bad_alloc & ba)
				{
					std::cout << "------ Нельзя выделить память на новую матрицу: " << ba.what() << std::endl;
					old_matr = erase(old_matr);
					return nullptr;
				}
				new_ptr->digit = ptr_line->digit;
				new_ptr->i = ptr_line->i;
				new_ptr->j = ptr_line->j;
				new_ptr->line = nullptr;
				new_ptr->next = nullptr;
				if (new_ptr_line !=nullptr )
					new_ptr_line->line = new_ptr;
				else {
					if (new_ptr_matr != nullptr) {
						new_ptr_matr->next = new_ptr;
						new_ptr_matr = new_ptr_matr->next;
					}
					else {
						new_matr = new_ptr;
						new_ptr_matr = new_matr;
					}
				}
				ptr_line = ptr_line->line;
			}
			new_ptr = nullptr;
			ptr = ptr->next;
		}
		return new_matr;
	}
	Matrix* Find(Matrix* &matr,int a, int n ,int &p) {
		Matrix* pre = nullptr;
		Matrix* pre_find=nullptr;
		Matrix* ptr_matr = matr;
		Matrix* ptr_line = nullptr;
		int count = 0;
		int h = 0;
		int c = 0;
		int count_max = 0;
		if (a == 0) {
			while (ptr_matr != nullptr) {
				ptr_line = ptr_matr;
				count = 0;
				while (ptr_line != nullptr) {
					if (ptr_line->digit > 0)
						count++;
					ptr_line = ptr_line->line;
				}
				if (count > count_max) {
					p = 1;
					pre_find = pre;
					count_max = count;
				}
				pre = ptr_matr;
				ptr_matr = ptr_matr->next;
			}
			return pre_find;
		}
		else
		{
			while (ptr_matr != nullptr) {
				if (ptr_matr->i == c) {
					ptr_line = ptr_matr;
					count = 0;
					int help = 0;
					h = 0;
					while (ptr_line != nullptr) {
						if (ptr_line->digit < 0)
							count++;
						count += ptr_line->j - h - help;
						h = ptr_line->j;
						help = 1;
						ptr_line = ptr_line->line;
					}
					count += n - h-1;
					if (count > count_max) {
						pre_find = pre;
						count_max = count;
					}
				}
				else {
					p = c;
					return nullptr;
				}
				pre = ptr_matr;
				c++;
				ptr_matr = ptr_matr->next;
			}
			if ((pre_find==nullptr)||(pre_find->next == pre))
				return nullptr;
			else
				return pre_find;
		}
	}
	Matrix* SwapLine(Matrix* matr, int a, int n,Matrix* (*f)(Matrix*&,int,int,int&)) {
		Matrix* ptr = nullptr;
		Matrix* save = nullptr;
		Matrix* ptr_save = nullptr;//сохранение нижней строки и замена на нулевую
		Matrix* pt = nullptr;
		int check = 0;
		ptr = f(matr,a,n,check);
		if (ptr != nullptr) {
			if ((a == 0) && (matr->i == 0))
			{
				pt = matr;
				while (pt != nullptr) {
					pt->i = ptr->next->i;
					pt = pt->line;
				}
				pt = ptr->next;
				while (pt != nullptr) {
					pt->i = 0;
					pt = pt->line;
				}
				if (ptr != matr) {
					save = matr->next;
					matr->next = ptr->next->next;
					ptr->next->next = save;
					save = ptr->next;
					ptr->next = matr;
					matr = save;
				}
				else {
					save = matr->next;
					matr->next = ptr->next->next;
					save->next = matr;
					matr = save;
				}

			}
			else
			{
				if ((a==0)&&(matr->i != 0)) {
					pt = ptr->next;
					while (pt != nullptr) {
						pt->i = 0;
						pt = pt->line;
					}
					save = ptr->next;
					ptr->next = ptr->next->next;
					save->next = matr;
					matr = save;
				}
				else {
					pt = matr;
					while (pt->next->next != nullptr)
						pt = pt->next;
					if (pt->next->i == a)
					{
						save = pt->next;
						while (save != nullptr) {
							save->i = ptr->next->i;
							save = save->line;
						}
						save = ptr->next;
						while (save != nullptr) {
							save->i = a;
							save = save->line;
						}
						if (ptr->next!=pt) {
							pt->next->next = ptr->next->next;
							save = ptr->next;
							ptr->next = pt->next;
							pt->next = save;
							save->next = nullptr;
						}
						else {
							save = pt->next;
							ptr->next = pt->next;
							pt->next = pt->next->next;
							save->next = pt;
						}
					}

				}
			}
		}
		else {
			if ((a == 0) && (matr->i != a)&&(check==1)) {
				pt = matr;
				while (pt != nullptr) {
					pt->i = 0;
					pt = pt->line;
				}
			}
			else
			{
				if ((a>0)&&(check!=0)) {
					ptr = matr;
					save = ptr;
					while (ptr->next != nullptr) {
						save = ptr;
						ptr = ptr->next;
					}
					if (ptr->i == a) {
						save->next = nullptr;
						pt = ptr;
						ptr_save = ptr;
						while (pt != nullptr) {
							pt->i = check;
							pt = pt->line;
						}
						ptr = matr;
						while ((ptr->next != nullptr) && (ptr->next->i < ptr_save->i))
							ptr = ptr->next;
						ptr_save->next = ptr->next;
						if(ptr_save!=ptr)
							ptr->next = ptr_save;
					}
				}
			}
		}
		return matr;
	}
}