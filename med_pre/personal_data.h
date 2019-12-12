#pragma once
class personal_data {
public:
	//поля с личными данными
	char name[50];
	char surname[50];
	unsigned age;
	char gender;
	//конструктор и методы
	personal_data();
	void put_data();
	void show_data();
};