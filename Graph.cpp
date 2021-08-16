#include<windows.h>
#include <conio.h>
#include "Graph.h"	//объявление классов
#include <math.h>
#include <string>
using namespace std;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//внешнее обявление глобальной переменной
extern HDC hdc;      // объявим  контекст устройства

// Макрос для проверки состояния клавиатуры – из ШАБЛОНА
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
/*----------------------------------------------------------------*/
/*             Р Е А Л И З А Ц И Я    М Е Т О Д О В               */
/*----------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА IFunction          */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
IFunction::IFunction()
{
}//end IFunction::IFunction()

 //--------------------------------------------------------------
 //деструктор
IFunction::~IFunction(void)   //формально пустое тело
{
}//end IFunction::~IFunction()

/*-----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Function          */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Function::Function() 
{
}//end Function::Function()

 //--------------------------------------------------------------
 //деструктор
Function::~Function(void)   //формально пустое тело
{
}//end Function::~Function()

 //--------------------------------------------------------------
 //вычисление координаты y для соответствующей функции
double Function::FindY(double X)
{
	return X;
}//end Function::~FindY

//--------------------------------------------------------------
//построение графика
void Function ::Graphic(double** mas, int n, int Length_osi, double X0, double Y0)
{
	HWND hW = GetConsoleWindow();
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN graphic = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));  //синий карандаш для построения графика
	HPEN osi = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));		//черный карандаш для построения осей
	double x, y;
	string number;											//номера для масштаба

	double** xy = new double* [2];							//массив с координатами
	xy[0] = new double[4];
	xy[0][0] = mas[0][0];
	xy[0][1] = mas[0][n - 1];
	xy[0][2] = X0;
	xy[0][3] = xy[0][2] + Length_osi;
	xy[1] = new double[4];
	xy[1][0] = mas[1][0];
	xy[1][1] = mas[1][0];
	xy[1][3] = Y0;
	xy[1][2] = xy[1][3] + Length_osi;

	double* xy_change = new double[2];	//измененные координаты точки для построения графика
	xy_change[0] = 0;					//координата х
	xy_change[1] = 0;					//координата y

	//поиск экстремумов функции
	for (int i = 0; i < n; i++)
	{
		if (mas[1][i] < xy[1][0])		//поиск максимума
		{
			xy[1][0] = mas[1][i];
		}//end if
		if (mas[0][i] > xy[1][1])		//поиск минимума
		{
			xy[1][1] = mas[0][i];
		}//end if
	}//end for

	SelectObject(hDC, osi);				//делаем карандаш активным
	x = scale(0, xy[0]);
	y = scale(0, xy[1]) - xy[1][2] + xy[1][3];

	//построение осей из заданной точки
	MoveToEx(hDC, x, y, NULL);			//перемещаемя в центр координатной плоскости
	LineTo(hDC, x + Length_osi, y);		//проводи линию вправо
	MoveToEx(hDC, x, y, NULL);			//перемещаемя в центр координатной плоскости
	LineTo(hDC, x - Length_osi, y);		//проводи линию влево
	MoveToEx(hDC, x, y, NULL);			//перемещаемя в центр координатной плоскости
	LineTo(hDC, x, y + Length_osi);		//проводи линию вниз
	MoveToEx(hDC, x, y, NULL);			//перемещаемя в центр координатной плоскости
	LineTo(hDC, x, y - Length_osi);		//проводи линию вверх

	SelectObject(hDC, graphic);			//деламем карандаш активным
	x = scale(mas[0][0], xy[0]);
	y = scale(mas[1][0], xy[1]) - xy[1][2] + xy[1][3];
	MoveToEx(hDC, x, y, NULL);			//перемещаемя в центр координатной плоскости
	for (int i = 1; i < n; i++)
	{
		x = scale(mas[0][i], xy[0]);
		y = scale(mas[1][i], xy[1]) - xy[1][2] + xy[1][3];
		LineTo(hDC, x, y);
	}//end for

	double buf_x = scale(1, xy[0]) - scale(0, xy[0]);
	double buf_y = scale(0, xy[1]) - xy[1][2] + xy[1][3] - (scale(1, xy[1]) - xy[1][2] + xy[1][3]);

	//построение масштаба по оси x
	for (int i = xy[0][0]; i <= xy[0][1]; i++)
	{
		if (i == 0) 
		{
			continue;
		}//end if

		xy_change[0] = scale(i, xy[0]);
		xy_change[1] = scale(0, xy[1]) - 5 - xy[1][2] + xy[1][3];

		MoveToEx(hDC, xy_change[0], xy_change[1], NULL);

		xy_change[1] = scale(0, xy[1]) + 5 - xy[1][2] + xy[1][3];

		LineTo(hDC, xy_change[0], xy_change[1]);

		number = to_string(i);										//перевод числа в строку
		TextOutA(hDC, xy_change[0] - 5, xy_change[1] + 10, number.c_str(), number.length());
	}//end for

	//построение масштаба по оси y
	for (int i = xy[1][0]; i <= xy[1][1]; i++)
	{
		xy_change[1] = scale(i, xy[1]) - xy[1][2] + xy[1][3];
		xy_change[0] = scale(0, xy[0]) + 5;

		MoveToEx(hDC, xy_change[0], xy_change[1], NULL);

		xy_change[0] = scale(0, xy[0]) - 5;

		LineTo(hDC, xy_change[0], xy_change[1]);

		number = to_string(i);										//перевод числа в строку
		TextOutA(hDC, xy_change[0] - 20, xy_change[1] - 5, number.c_str(), number.length());
	}//end for

	DeleteObject(graphic);					// Уничтожим нами созданные объекты
	DeleteObject(osi);						// Уничтожим нами созданные объекты
	ReleaseDC(hW, hDC);
}//end Function ::Graphic

 //--------------------------------------------------------------
 //масштабирование
double Function::scale(double x, double* koef)
{
	return (((x - koef[0]) / (koef[1] - koef[0]))
		* (koef[3] - koef[2])) + koef[2];
}//end Function::scale

/*-----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Parabola          */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Parabola::Parabola() : Function()
{
}//end Parabola::Parabola()

 //--------------------------------------------------------------
 //деструктор
Parabola::~Parabola(void)   //формально пустое тело
{
}//end Parabola::~Parabola()

 //--------------------------------------------------------------
 //вычисление координаты y для соответствующей функции
double Parabola::FindY(double X)
{
	return X * X;
}//end Parabola::FindY

/*-----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Exponenta          */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Exponenta::Exponenta() :Function()
{
}//end Exponenta::Exponenta()

 //--------------------------------------------------------------
 //деструктор
Exponenta::~Exponenta(void)   //формально пустое тело
{
}//end Exponenta::~Exponenta()

 //--------------------------------------------------------------
 //вычисление координаты y для соответствующей функции
double Exponenta::FindY(double X)
{
    return exp(X);
}//end Exponenta::FindY

/*-----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Function          */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Modul::Modul() :Function()
{
}//end Function::Function()

 //--------------------------------------------------------------
 //деструктор
Modul::~Modul(void)   //формально пустое тело
{
}//end Modul::~Modul()

 //--------------------------------------------------------------
 //вычисление координаты y для соответствующей функции
double Modul::FindY(double X)
{
    return fabs(X);
}//end Modul::FindY()

/*-----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Function          */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Sinus::Sinus() :Function()
{
}//end Function::Function()

 //--------------------------------------------------------------
 //деструктор
Sinus::~Sinus(void)   //формально пустое тело
{
}//end Sinus::~Sinus()

 //--------------------------------------------------------------
 //вычисление координаты y для соответствующей функции
double Sinus::FindY(double X)
{
    return sin(X);
}//end Sinus::FindY