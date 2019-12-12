#include "stdafx.h"
#include <iostream>
#include "presure_data.h"
using std::cout;
using std::cin;
using std::endl;
//конструктор 
pressure_data::pressure_data() : up_pressure(0), down_pressure(0) {};//конструктор по умолчанию
//методы класса
void pressure_data::put_data() {
	char temp;
	cout << "Введите значение вашего давления в форме: верхнее значение/нижнее значение (например, 120/70).\n" << endl;
	cin >> up_pressure >> temp >> down_pressure;
}
void pressure_data::show_data() {
	char temp = '/';
	cout << up_pressure << temp << down_pressure << "  " << endl;
}