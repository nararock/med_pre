// med_pre.cpp : Defines the entry point for the console application.
//

// pressure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> // для файловых потоков
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>//для получения текущей даты и времени
using namespace std;
///////////////////////////////////////////////////////////
struct personal_data {//структура для хранения личных данных
	char name[50];
	char surname[50];
	unsigned age;
	char gender;
	personal_data() : name("\0"), surname("\0"), age(0), gender('\0') {};//конструктор по умолчанию
	void put_data() {//заполнение полей структуры
		cout << "Введите ваше имя (строчными буквами)" << endl;
		cin >> name;
		cout << "Введите ваше фамилия (строчными буквами)" << endl;
		cin >> surname;
		cout << "Введите ваш возраст" << endl;
		cin >> age;
		cout << "Введите ваш пол: ж - если женщина, м - если мужчина" << endl;
		cin >> gender;
	}
	void show_data() {//вывод полей структуры
		cout << "Имя: " << name << endl;
		cout << "Фамилия: " << surname << endl;
		cout << "Пол: " << gender << endl;
		cout << "Возраст: " << age << endl;
		cout << " " << endl;
	}
};
struct pressure_data {//структура для хранения значений давления
	int up_pressure;
	int down_pressure;
	pressure_data() : up_pressure(0), down_pressure(0) {};//конструктор по умолчанию
	void put_data (){
	char temp;
	cout << "Введите значение вашего давления в форме: верхнее значение/нижнее значение (например, 120/70).\n" << endl;
	cin >> up_pressure >> temp >> down_pressure;
	}
	void show_data() {
		char temp = '/';
		cout << up_pressure << temp << down_pressure << "  " << endl;
	}
};
/////////////////////////////////////////////////////////////////
class man {//карточка пациента (личные данные, значение давления)
private:
	personal_data person;
	pressure_data pressure;
		
public:
	man() : person(), pressure() {};
	void put() {//запросить личные данные
		person.put_data();
	}
	void put_pressure() {//запись значений давления
		pressure.put_data();
		system("cls");
	}
	void create_name(char (&temp)[105]) {//создание персонального имени для файла из данных класса
		char dat[5] = { ".dat" };
		strcat_s(temp, person.name);
		strcat_s(temp, person.surname);
		strcat_s(temp, dat);
	}
	void show_persondate() {//вывод персональных данных
		person.show_data();
	}
	void save_person_data() {//сохранение персональных данных
		char temp[105] = {};//формируем имя для файла
		create_name(temp);//название для файла
		ofstream outfile(temp, ios::binary| ios::out | ios::app);//создаем выходной поток для записи файла с названием temp
		outfile.write(reinterpret_cast<char*>(&person), sizeof(person));//записываем в двоичный файл личные данные (структура)
		outfile.close();
	}
	void save_pressure_data() {
		////////////////////////////////////
		struct tm newtime;//хранение текущей даты и времени
		time_t now = time(0);
		localtime_s(&newtime, &now);
		/////////////////////////////////////
		char temp[105] = {};//формируем имя для файла
		create_name(temp);//название для файла
		ofstream outfile;
		outfile.open(temp, ios::binary | ios::out | ios::app | ios :: _Nocreate);//создаем выходной поток для записи файла с названием temp
		if (outfile)
		{
			outfile.seekp(0, ios::end);//передвигаем указатель в конец файла
			outfile.write(reinterpret_cast<char*>(&pressure), sizeof(pressure));//записываем структуру со значением давления в конец файла
			outfile.seekp(0, ios::end);
			outfile.write(reinterpret_cast<char*>(&newtime), sizeof(newtime));//записываем время записи
			outfile.close();
		} else
		{
			cout << "Запись давления не была осуществлена."
				<< "Файл с именем " << temp << " не был создан ранее для записи личных данных." << endl;
		}
		
	}
	bool read_personal_data() {
		cout << "Вход в ваш кабинет" << endl;
		string temp_name, temp_surname, temp;
		cout << "Введите ваше имя (строчными буквами)" << endl;
		cin >> temp_name;
		cout << "Введите ваше фамилия (строчными буквами)" << endl;
		cin >> temp_surname;
		temp = temp_name + temp_surname + ".dat";//находим название файла
		ifstream infile(temp, ios::binary);//поток для чтения
		if (!infile) {
			cout << "Ошибка открытия файла или файл не существует!" << endl;
			return false;
		}
		infile.seekg(0, ios::beg);//устанавливаем указатель на начало файла
		infile.read(reinterpret_cast<char*>(&person), sizeof(person));//читаем личные данные в структуру personal_data
		cout << "Личный кабинет открыт" << endl;
		infile.close();
		return true;
	}
	unsigned number_of_datapressure() {//возвращает количество записанных значений давления
		char temp[105] = {};//формируем имя для файла
		create_name(temp);//название для файла
		ifstream infile(temp, ios::binary);//поток для чтения
		infile.seekg(0, ios::end);//находим количество значений давления в файле
		int size_pressure = infile.tellg();
		unsigned number_of_pressure = (size_pressure - sizeof(person)) / sizeof(pressure);
		return number_of_pressure;
	}
	void read_pressure(unsigned int n) {//считывает последние n значений
		char temp[105] = {};//формируем имя для файла
		create_name(temp);//название для файла
		ifstream infile(temp, ios::binary);//поток для чтения
		unsigned int number_of_pressure = number_of_datapressure();
		if (number_of_pressure < n) {
			cout << "У вас только " << number_of_pressure << " записанных значений давления" << endl;
			n = number_of_pressure;
		}
		infile.seekg(n * sizeof(pressure), ios::end);//переставляем указатель на данные c давлением
		for (unsigned int i = 0; i < n; i++) {//вывод n значений давления
			infile.read(reinterpret_cast<char*>(&pressure), sizeof(pressure));
			pressure.show_data();
		}
		cout << endl;
	}
}; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
