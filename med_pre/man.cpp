#include "stdafx.h"
#include <iostream>
#include <fstream> // ��� �������� �������
#include <string>
#include "man.h"
using namespace std;
man::man() : person(), pressure() {};
void man:: put() {//��������� ������ ������
	person.put_data();
}
void man::put_pressure() {//������ �������� ��������
	pressure.put_data();
	system("cls");
}
void man::create_name(char(&temp)[105]) {//�������� ������������� ����� ��� ����� �� ������ ������
	char dat[5] = { ".dat" };
	strcat_s(temp, person.name);
	strcat_s(temp, person.surname);
	strcat_s(temp, dat);
}
void man::show_persondate() {//����� ������������ ������
	person.show_data();
}
void man::save_person_data() {//���������� ������������ ������
	char temp[105] = {};//��������� ��� ��� �����
	create_name(temp);//�������� ��� �����
	ofstream outfile(temp, ios::binary | ios::out | ios::app);//������� �������� ����� ��� ������ ����� � ��������� temp
	outfile.write(reinterpret_cast<char*>(&person), sizeof(person));//���������� � �������� ���� ������ ������ (���������)
	outfile.close();
}
void man::save_pressure_data() {
	char temp[105] = {};//��������� ��� ��� �����
	create_name(temp);//�������� ��� �����
	ofstream outfile;
	outfile.open(temp, ios::binary | ios::out | ios::app | ios::_Nocreate);//������� �������� ����� ��� ������ ����� � ��������� temp
	if (outfile){
		//outfile.seekp(0, ios::end);//����������� ��������� � ����� �����
		outfile.write(reinterpret_cast<char*>(&pressure), sizeof(pressure));//���������� ��������� �� ��������� �������� � ����� �����
		outfile.close();
	}
	else
		{
		cout << "������ �������� �� ���� ������������."
		<< "���� � ������ " << temp << " �� ��� ������ ����� ��� ������ ������ ������." << endl;
		}
}
bool man::read_personal_data() {
	cout << "���� � ��� �������" << endl;
	string temp_name, temp_surname, temp;
	cout << "������� ���� ��� (��������� �������)" << endl;
	cin >> temp_name;
	cout << "������� ���� ������� (��������� �������)" << endl;
	cin >> temp_surname;
	temp = temp_name + temp_surname + ".dat";//������� �������� �����
	ifstream infile(temp, ios::binary);//����� ��� ������
	if (!infile) {
		cout << "������ �������� ����� ��� ���� �� ����������!" << endl;
		return false;
	}
	infile.seekg(0, ios::beg);//������������� ��������� �� ������ �����
	infile.read(reinterpret_cast<char*>(&person), sizeof(person));//������ ������ ������ � ��������� personal_data
	cout << "������ ������� ������" << endl;
	infile.close();
	return true;
}
unsigned man::number_of_datapressure() {//���������� ���������� ���������� �������� ��������
	char temp[105] = {};//��������� ��� ��� �����
	create_name(temp);//�������� ��� �����
	ifstream infile(temp, ios::binary);//����� ��� ������
	infile.seekg(0, ios::end);//������� ���������� �������� �������� � �����
	int size_pressure = infile.tellg();
	unsigned number_of_pressure = (size_pressure - sizeof(person)) / sizeof(pressure);
	return number_of_pressure;
}
void man::read_pressure(unsigned int n) {//��������� ��������� n ��������
	char temp[105] = {};//��������� ��� ��� �����
	create_name(temp);//�������� ��� �����
	ifstream infile(temp, ios::binary);//����� ��� ������
	unsigned int number_of_pressure = number_of_datapressure();
	if (number_of_pressure < n) {
		cout << "� ��� ������ " << number_of_pressure << " ���������� �������� ��������" << endl;
		n = number_of_pressure;
	}
	for (unsigned int i = 0; i < n; i++) {//����� n �������� ��������
		infile.seekg((-1)*(signed)((i + 1) * sizeof(pressure)), ios::end);//������������ ��������� �� ������ c ���������
		infile.read(reinterpret_cast<char*>(&pressure), sizeof(pressure));
		pressure.show_data();
	}
	cout << endl;
}
