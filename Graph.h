#pragma once
/*-----------------------------------------------------------------------*/
/*                         � � � �    � � � � � �                        */
/*-----------------------------------------------------------------------*/

  /*-----------------------  ��������� ������� ----------------------------------*/
class IFunction
{
public:
	IFunction();								//�����������						
	~IFunction();								//����������
	virtual double FindY(double X) = 0;
	virtual void Graphic(double** mas, int n, int Length_osi, double X0, double Y0) = 0;
	virtual double scale(double arg, double* koeffs) = 0;
};

  /*-----------------------  ����� ������� ----------------------------------*/
class Function : public IFunction
{
public:
	Function();							//�����������
	~Function();						//����������
	virtual double FindY(double X);		//���������� ���������� y ��� ��������������� �������
	virtual void Graphic(double** mas, int n, int Length_osi, double X0, double Y0);//���������� �������
	virtual double scale(double arg, double* koeffs);//���������������
};//end class Function

/*-----------------------  ����� �������� ----------------------------------*/
class Parabola : public Function
{
public:
	Parabola();							//�����������
	~Parabola();						//����������
	double FindY(double X);				//���������� ���������� y ��� ��������������� �������
};//end class Parabola

/*-----------------------  ����� ���������� ----------------------------------*/
class Exponenta : public Function
{
public:
	Exponenta();						//�����������
	~Exponenta();						//����������
	double FindY(double X);				//���������� ���������� y ��� ��������������� �������
};//end class Exponenta

/*-----------------------  ����� ������ ----------------------------------*/
class Modul : public Function
{
public:
	Modul();						//�����������
	~Modul();						//����������
	double FindY(double X);			//���������� ���������� y ��� ��������������� �������
};//end class Modul

/*-----------------------  ����� ����� ----------------------------------*/
class Sinus : public Function
{
public:
	Sinus();						//�����������
	~Sinus();						//����������
	double FindY(double X);			//���������� ���������� y ��� ��������������� �������
};//end class Sinus