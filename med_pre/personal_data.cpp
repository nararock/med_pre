#include "stdafx.h"
#include <iostream>
#include "personal_data.h"
using std::cout;
using std::cin;
using std::endl;
//конструктор класса
personal_data::personal_data() : name("\0"), surname("\0"), age(0), gender('\0') {};//конструктор по умолчанию
//методы класса
void personal_data::put_data() {//заполнение полей структуры
		cout << "Введите ваше имя (строчными буквами)" << endl;
		cin >> name;
		cout << "Введите ваше фамилия (строчными буквами)" << endl;
		cin >> surname;
		cout << "Введите ваш возраст" << endl;
		cin >> age;
		cout << "Введите ваш пол: ж - если женщина, м - если мужчина" << endl;
		cin >> gender;
}
void personal_data::show_data() {//вывод полей структуры
		cout << "Имя: " << name << endl;
		cout << "Фамилия: " << surname << endl;
		cout << "Пол: " << gender << endl;
		cout << "Возраст: " << age << endl;
		cout << " " << endl;
}
