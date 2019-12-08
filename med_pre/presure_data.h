#pragma once
class pressure_data {//структура для хранения значений давления
public:
	int up_pressure;
	int down_pressure;
	pressure_data();
	void put_data();
	void show_data();
};