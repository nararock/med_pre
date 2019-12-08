#pragma once
#include "personal_data.h"//хранение личных данных
#include "presure_data.h"//хранение значений давления
class man {//карточка пациента (личные данные, значение давления)
private:
	personal_data person;
	pressure_data pressure;
public:
	man();
	void put();
	void put_pressure();
	void create_name(char(&temp)[105]);
	void show_persondate();
	void save_person_data();
	void save_pressure_data();
	bool read_personal_data();
	unsigned number_of_datapressure();
	void read_pressure(unsigned int n);
};