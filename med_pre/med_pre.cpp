// med_pre.cpp : Defines the entry point for the console application.
//

// pressure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "man.h"//карточка клиента 
using namespace std;

int main()
{
	system("chcp 1251 > text");
	setlocale(LC_ALL, "Russian");//ввод по-русски
	man m;
	string answer;
	while (true) {
		cout << "У вас есть личный кабинет? (введите да  или  нет)" << endl;
		cin >> answer;
		if (answer == "нет") {//если кабинета нет, то создается объект класса и данные записываются в файл
			m.put();
			m.save_person_data();
			system("cls");
			break;
		}
		else if (answer == "да") {
			system("cls");
			if (m.read_personal_data()) {
				break;
			}
			else { continue;}
		}
		else {
			cout << "Вы ввели неверный ответ, попробуйте запустить программу еще раз" << endl;
			continue;
		}
	}
	
	bool status = false;
	do {
		cout << "Выберите действие (введите номер выбранного действия): \n"
			<< "1 - Вывести результаты измерения давления;\n"
			<< "2 - Добавить результаты измерения давления;\n"
			<< "3 - Просмотреть данные о себе;\n"
			<< "4 - Сохранить данные;\n"
			<< "5 - Выход из программы." << endl;
		cin >> answer;
		system("cls");
		if (answer == "1") {
			int count = m.number_of_datapressure();//количество записей значений
			int n;
			cout << "У вас " << count << " записей давления.\n"
				<< "Сколько последних записей давления вывести на экран? Введите количество: ";
			cin >> n;
			m.read_pressure(n);
		}
		else if (answer == "2") {
			m.put_pressure();
		}
		else if (answer == "3") {
			m.show_persondate();
		}
		else if (answer == "4") {
			m.save_pressure_data();
			status = true;
		}
		else if (answer == "5") {
			if (status == false) {
				string temp;
				cout << "Ваши данные не сохранены.\n"
					<< "Хотите сохранить? Введите да (и выберите пункт №4) или нет.\n";
				cin >> temp;
				if (temp == "да") {
					continue;
				}
			}
		}
	} while (answer != "5");
	return 0;
}
