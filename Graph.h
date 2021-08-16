#pragma once
/*-----------------------------------------------------------------------*/
/*                         Т И П Ы    Д А Н Н Ы Х                        */
/*-----------------------------------------------------------------------*/

  /*-----------------------  Интерфейс ФУНКЦИИ ----------------------------------*/
class IFunction
{
public:
	IFunction();								//конструктор						
	~IFunction();								//деструктор
	virtual double FindY(double X) = 0;
	virtual void Graphic(double** mas, int n, int Length_osi, double X0, double Y0) = 0;
	virtual double scale(double arg, double* koeffs) = 0;
};

  /*-----------------------  Класс ФУНКЦИЯ ----------------------------------*/
class Function : public IFunction
{
public:
	Function();							//конструктор
	~Function();						//деструктор
	virtual double FindY(double X);		//вычисление координаты y для соответствующей функции
	virtual void Graphic(double** mas, int n, int Length_osi, double X0, double Y0);//построение графика
	virtual double scale(double arg, double* koeffs);//масштабирование
};//end class Function

/*-----------------------  Класс ПАРАБОЛА ----------------------------------*/
class Parabola : public Function
{
public:
	Parabola();							//конструктор
	~Parabola();						//деструктор
	double FindY(double X);				//вычисление координаты y для соответствующей функции
};//end class Parabola

/*-----------------------  Класс ЭКСПОНЕНТА ----------------------------------*/
class Exponenta : public Function
{
public:
	Exponenta();						//конструктор
	~Exponenta();						//деструктор
	double FindY(double X);				//вычисление координаты y для соответствующей функции
};//end class Exponenta

/*-----------------------  Класс МОДУЛЬ ----------------------------------*/
class Modul : public Function
{
public:
	Modul();						//конструктор
	~Modul();						//деструктор
	double FindY(double X);			//вычисление координаты y для соответствующей функции
};//end class Modul

/*-----------------------  Класс СИНУС ----------------------------------*/
class Sinus : public Function
{
public:
	Sinus();						//конструктор
	~Sinus();						//деструктор
	double FindY(double X);			//вычисление координаты y для соответствующей функции
};//end class Sinus