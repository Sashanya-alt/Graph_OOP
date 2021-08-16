#include<windows.h>
#include <conio.h>
#include "Graph.h"	//���������� �������
#include <math.h>
#include <string>
using namespace std;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   � � � � � � � � � �   � � � � � � � � � �  �  � � � � � � � � �   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//������� ��������� ���������� ����������
extern HDC hdc;      // �������  �������� ����������

// ������ ��� �������� ��������� ���������� � �� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
/*----------------------------------------------------------------*/
/*             � � � � � � � � � �    � � � � � � �               */
/*----------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*        ������ ������ IFunction          */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
IFunction::IFunction()
{
}//end IFunction::IFunction()

 //--------------------------------------------------------------
 //����������
IFunction::~IFunction(void)   //��������� ������ ����
{
}//end IFunction::~IFunction()

/*-----------------------------------------------------------------------*/
/*        ������ ������ Function          */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Function::Function() 
{
}//end Function::Function()

 //--------------------------------------------------------------
 //����������
Function::~Function(void)   //��������� ������ ����
{
}//end Function::~Function()

 //--------------------------------------------------------------
 //���������� ���������� y ��� ��������������� �������
double Function::FindY(double X)
{
	return X;
}//end Function::~FindY

//--------------------------------------------------------------
//���������� �������
void Function ::Graphic(double** mas, int n, int Length_osi, double X0, double Y0)
{
	HWND hW = GetConsoleWindow();
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN graphic = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));  //����� �������� ��� ���������� �������
	HPEN osi = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));		//������ �������� ��� ���������� ����
	double x, y;
	string number;											//������ ��� ��������

	double** xy = new double* [2];							//������ � ������������
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

	double* xy_change = new double[2];	//���������� ���������� ����� ��� ���������� �������
	xy_change[0] = 0;					//���������� �
	xy_change[1] = 0;					//���������� y

	//����� ����������� �������
	for (int i = 0; i < n; i++)
	{
		if (mas[1][i] < xy[1][0])		//����� ���������
		{
			xy[1][0] = mas[1][i];
		}//end if
		if (mas[0][i] > xy[1][1])		//����� ��������
		{
			xy[1][1] = mas[0][i];
		}//end if
	}//end for

	SelectObject(hDC, osi);				//������ �������� ��������
	x = scale(0, xy[0]);
	y = scale(0, xy[1]) - xy[1][2] + xy[1][3];

	//���������� ���� �� �������� �����
	MoveToEx(hDC, x, y, NULL);			//����������� � ����� ������������ ���������
	LineTo(hDC, x + Length_osi, y);		//������� ����� ������
	MoveToEx(hDC, x, y, NULL);			//����������� � ����� ������������ ���������
	LineTo(hDC, x - Length_osi, y);		//������� ����� �����
	MoveToEx(hDC, x, y, NULL);			//����������� � ����� ������������ ���������
	LineTo(hDC, x, y + Length_osi);		//������� ����� ����
	MoveToEx(hDC, x, y, NULL);			//����������� � ����� ������������ ���������
	LineTo(hDC, x, y - Length_osi);		//������� ����� �����

	SelectObject(hDC, graphic);			//������� �������� ��������
	x = scale(mas[0][0], xy[0]);
	y = scale(mas[1][0], xy[1]) - xy[1][2] + xy[1][3];
	MoveToEx(hDC, x, y, NULL);			//����������� � ����� ������������ ���������
	for (int i = 1; i < n; i++)
	{
		x = scale(mas[0][i], xy[0]);
		y = scale(mas[1][i], xy[1]) - xy[1][2] + xy[1][3];
		LineTo(hDC, x, y);
	}//end for

	double buf_x = scale(1, xy[0]) - scale(0, xy[0]);
	double buf_y = scale(0, xy[1]) - xy[1][2] + xy[1][3] - (scale(1, xy[1]) - xy[1][2] + xy[1][3]);

	//���������� �������� �� ��� x
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

		number = to_string(i);										//������� ����� � ������
		TextOutA(hDC, xy_change[0] - 5, xy_change[1] + 10, number.c_str(), number.length());
	}//end for

	//���������� �������� �� ��� y
	for (int i = xy[1][0]; i <= xy[1][1]; i++)
	{
		xy_change[1] = scale(i, xy[1]) - xy[1][2] + xy[1][3];
		xy_change[0] = scale(0, xy[0]) + 5;

		MoveToEx(hDC, xy_change[0], xy_change[1], NULL);

		xy_change[0] = scale(0, xy[0]) - 5;

		LineTo(hDC, xy_change[0], xy_change[1]);

		number = to_string(i);										//������� ����� � ������
		TextOutA(hDC, xy_change[0] - 20, xy_change[1] - 5, number.c_str(), number.length());
	}//end for

	DeleteObject(graphic);					// ��������� ���� ��������� �������
	DeleteObject(osi);						// ��������� ���� ��������� �������
	ReleaseDC(hW, hDC);
}//end Function ::Graphic

 //--------------------------------------------------------------
 //���������������
double Function::scale(double x, double* koef)
{
	return (((x - koef[0]) / (koef[1] - koef[0]))
		* (koef[3] - koef[2])) + koef[2];
}//end Function::scale

/*-----------------------------------------------------------------------*/
/*        ������ ������ Parabola          */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Parabola::Parabola() : Function()
{
}//end Parabola::Parabola()

 //--------------------------------------------------------------
 //����������
Parabola::~Parabola(void)   //��������� ������ ����
{
}//end Parabola::~Parabola()

 //--------------------------------------------------------------
 //���������� ���������� y ��� ��������������� �������
double Parabola::FindY(double X)
{
	return X * X;
}//end Parabola::FindY

/*-----------------------------------------------------------------------*/
/*        ������ ������ Exponenta          */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Exponenta::Exponenta() :Function()
{
}//end Exponenta::Exponenta()

 //--------------------------------------------------------------
 //����������
Exponenta::~Exponenta(void)   //��������� ������ ����
{
}//end Exponenta::~Exponenta()

 //--------------------------------------------------------------
 //���������� ���������� y ��� ��������������� �������
double Exponenta::FindY(double X)
{
    return exp(X);
}//end Exponenta::FindY

/*-----------------------------------------------------------------------*/
/*        ������ ������ Function          */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Modul::Modul() :Function()
{
}//end Function::Function()

 //--------------------------------------------------------------
 //����������
Modul::~Modul(void)   //��������� ������ ����
{
}//end Modul::~Modul()

 //--------------------------------------------------------------
 //���������� ���������� y ��� ��������������� �������
double Modul::FindY(double X)
{
    return fabs(X);
}//end Modul::FindY()

/*-----------------------------------------------------------------------*/
/*        ������ ������ Function          */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Sinus::Sinus() :Function()
{
}//end Function::Function()

 //--------------------------------------------------------------
 //����������
Sinus::~Sinus(void)   //��������� ������ ����
{
}//end Sinus::~Sinus()

 //--------------------------------------------------------------
 //���������� ���������� y ��� ��������������� �������
double Sinus::FindY(double X)
{
    return sin(X);
}//end Sinus::FindY