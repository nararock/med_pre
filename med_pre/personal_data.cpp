#include "stdafx.h"
#include <iostream>
#include "personal_data.h"
using std::cout;
using std::cin;
using std::endl;
//����������� ������
personal_data::personal_data() : name("\0"), surname("\0"), age(0), gender('\0') {};//����������� �� ���������
//������ ������
void personal_data::put_data() {//���������� ����� ���������
		cout << "������� ���� ��� (��������� �������)" << endl;
		cin >> name;
		cout << "������� ���� ������� (��������� �������)" << endl;
		cin >> surname;
		cout << "������� ��� �������" << endl;
		cin >> age;
		cout << "������� ��� ���: � - ���� �������, � - ���� �������" << endl;
		cin >> gender;
}
void personal_data::show_data() {//����� ����� ���������
		cout << "���: " << name << endl;
		cout << "�������: " << surname << endl;
		cout << "���: " << gender << endl;
		cout << "�������: " << age << endl;
		cout << " " << endl;
}
