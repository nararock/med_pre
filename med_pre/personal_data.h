#pragma once
class personal_data {
public:
	//���� � ������� �������
	char name[50];
	char surname[50];
	unsigned age;
	char gender;
	//����������� � ������
	personal_data();
	void put_data();
	void show_data();
};