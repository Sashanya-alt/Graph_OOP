#pragma once      

#include <windows.h>
#include <conio.h>
#include <sstream>
#include <iostream>
using namespace std;        // Пространство имен std

#include "Graph.h"
#include "GetConWin.h"		//указатель на консольное окно

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;

const int Length_osi = 300;		//длина половины оси
const int X0 = 200;				//координата х для начала координат
const int Y0 = 600;				//координата у для начала координат

/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/
int main()
{
	setlocale(LC_ALL, "RUSSIAN");		//подключение русского языка
	system("color FF");					//экран белый, буквы черные
	system("cls");						//очистка экрана

	double Step = 0.01;					//шаг через которй вычисляются координаты графика
	double a, b;						//начало и конец отрезка, на котром необходимо построить график
	int Num;							//номер необходимого графика
	int k;								//количество шагов, входящих в отрезок

	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();

	if (hwnd == NULL)
	{
		return -1;
	}//end if

	//получение контекста устройства для консольного окна
	hdc = GetWindowDC(hwnd);

	if (hdc == 0)						//если контекст существует
	{
		return -1;
	}//end if

	//вывод на экран сообщения
	cout << "Введите цифру соответствующую необходимому графику\n";
	cout << "0) y = x\n1) y = x^2\n2) y = exp(x)\n3) y = |X|\n4) y = sin(x)\t";
	cin >> Num;							//считываем введенное число

	//вывод на экран сообщения
	cout << "\nВведите отрезок на котором необходимо построить графиу функции";
	cout << "\nВведите начало отрезка\t";
	cin >> a;							//считываем введенное число
	cout << "Введите конец отрезка\t";
	cin >> b;							//считываем введенное число

	k = (int)(abs(b - a) / Step) + 1;	//вычисления количество шагов, входящих в отрезок
	
	double** mas_xy = new double* [2];	//массив координат точек, по которым будет построен график
	mas_xy[0] = new double[k];			//координаты х
	mas_xy[1] = new double[k];			//координаты у

	//объявление графиков
	Function Graphic;
	Parabola Graph_parab;
	Exponenta Graph_exp;
	Modul Graph_fabs;
	Sinus Graph_sin;

	//абстрактный класс для графиков
	Function* Function[5];
	Function[0] = &Graphic;
	Function[1] = &Graph_parab;
	Function[2] = &Graph_exp;
	Function[3] = &Graph_fabs;
	Function[4] = &Graph_sin;

	//вычисление координат графика и запись их в массив
	for (int i = 0; i < k; i++)
	{
		mas_xy[0][i] = a + Step * i;						//для координаты х
		mas_xy[1][i] = Function[Num]->FindY(mas_xy[0][i]);	//для координаты у
	}//end for

	//построение графика
	Function[Num]->Graphic(mas_xy, k, Length_osi, X0, Y0);

}//end main