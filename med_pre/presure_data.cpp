#include "stdafx.h"
#include <iostream>
#include "presure_data.h"
using std::cout;
using std::cin;
using std::endl;
//����������� 
pressure_data::pressure_data() : up_pressure(0), down_pressure(0) {};//����������� �� ���������
//������ ������
void pressure_data::put_data() {
	char temp;
	cout << "������� �������� ������ �������� � �����: ������� ��������/������ �������� (��������, 120/70).\n" << endl;
	cin >> up_pressure >> temp >> down_pressure;
}
void pressure_data::show_data() {
	char temp = '/';
	cout << up_pressure << temp << down_pressure << "  " << endl;
}