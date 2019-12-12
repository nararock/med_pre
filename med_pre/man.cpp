#include "stdafx.h"
#include <iostream>
#include <fstream> // для файловых потоков
#include <string>
#include "man.h"
using namespace std;
man::man() : person(), pressure() {};
void man:: put() {//запросить личные данные
	person.put_data();
}
void man::put_pressure() {//запись значений давления
	pressure.put_data();
	system("cls");
}
void man::create_name(char(&temp)[105]) {//создание персонального имени для файла из данных класса
	char dat[5] = { ".dat" };
	strcat_s(temp, person.name);
	strcat_s(temp, person.surname);
	strcat_s(temp, dat);
}
void man::show_persondate() {//вывод персональных данных
	person.show_data();
}
void man::save_person_data() {//сохранение персональных данных
	char temp[105] = {};//формируем имя для файла
	create_name(temp);//название для файла
	ofstream outfile(temp, ios::binary | ios::out | ios::app);//создаем выходной поток для записи файла с названием temp
	outfile.write(reinterpret_cast<char*>(&person), sizeof(person));//записываем в двоичный файл личные данные (структура)
	outfile.close();
}
void man::save_pressure_data() {
	char temp[105] = {};//формируем имя для файла
	create_name(temp);//название для файла
	ofstream outfile;
	outfile.open(temp, ios::binary | ios::out | ios::app | ios::_Nocreate);//создаем выходной поток для записи файла с названием temp
	if (outfile){
		//outfile.seekp(0, ios::end);//передвигаем указатель в конец файла
		outfile.write(reinterpret_cast<char*>(&pressure), sizeof(pressure));//записываем структуру со значением давления в конец файла
		outfile.close();
	}
	else
		{
		cout << "Запись давления не была осуществлена."
		<< "Файл с именем " << temp << " не был создан ранее для записи личных данных." << endl;
		}
}
bool man::read_personal_data() {
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
unsigned man::number_of_datapressure() {//возвращает количество записанных значений давления
	char temp[105] = {};//формируем имя для файла
	create_name(temp);//название для файла
	ifstream infile(temp, ios::binary);//поток для чтения
	infile.seekg(0, ios::end);//находим количество значений давления в файле
	int size_pressure = infile.tellg();
	unsigned number_of_pressure = (size_pressure - sizeof(person)) / sizeof(pressure);
	return number_of_pressure;
}
void man::read_pressure(unsigned int n) {//считывает последние n значений
	char temp[105] = {};//формируем имя для файла
	create_name(temp);//название для файла
	ifstream infile(temp, ios::binary);//поток для чтения
	unsigned int number_of_pressure = number_of_datapressure();
	if (number_of_pressure < n) {
		cout << "У вас только " << number_of_pressure << " записанных значений давления" << endl;
		n = number_of_pressure;
	}
	for (unsigned int i = 0; i < n; i++) {//вывод n значений давления
		infile.seekg((-1)*(signed)((i + 1) * sizeof(pressure)), ios::end);//переставляем указатель на данные c давлением
		infile.read(reinterpret_cast<char*>(&pressure), sizeof(pressure));
		pressure.show_data();
	}
	cout << endl;
}
