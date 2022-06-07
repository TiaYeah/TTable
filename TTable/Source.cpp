#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "../TTable/TSortTable.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TTreeTable.h"
#include "TArrayHashTable.h"
#include "TBalTree.h"

using namespace std;

TTable* table;
bool result = true;
int eff = 0;

void createTable(int _type)
{
	switch (_type)
	{
	case 1: {
		table = new TScanTable();
		break;
	}

	case 2: {
		table = new TSortTable();
		break;
	}

	case 3: {
		table = new TArrayHashTable();
		break;
	}

	case 4: {
		table = new TTreeTable();
		break;
	}
	case 5: {
		table = new TBalTree();
		break;
	}
	default:
		break;
	}

	srand(time(NULL));

	TRecord insertRec;
	for (int i = 0; i < 10; i++) {
		insertRec.key = rand() % 100;
		string str = "";
		for (int j = 0; j < 5; j++) {
			str += 'a' + rand() % 26;
		}
		insertRec.val = str;
		table->insert(insertRec);
	}

	cout << "��������� �������: \n";
	table->print(cout);
}

void insertIntoTable()
{
	TRecord rec;
	cout << "������� ���� � ������ " << endl;
	cin >> rec.key >> rec.val;


	eff = table->getEff();
	if (table->insert(rec)) {
		cout << "������� ���������" << endl;
	}
	else {
		cout << "������� �� ���������" << endl;
	}
	cout << "�������������:\n" << table->getEff() - eff << endl;
}

void findKey()
{
	TKey key;
	cout << "������� ���� ��� ������ " << endl;
	cin >> key;

	eff = table->getEff();
	if (table->find(key)) {
		cout << "������� ������" << endl;
	}
	else {
		cout << "������� �� ������" << endl;
	}
	cout << "�������������:\n" << table->getEff() - eff << endl;
}

void deleteKey()
{
	TKey key;
	cout << "������� ���� ��� �������� " << endl;
	cin >> key;

	eff = table->getEff();
	if (table->del(key)) {
		cout << "������� ������" << endl;
	}
	else {
		cout << "������� �� ������" << endl;
	}
	cout << "�������������:\n" << table->getEff() - eff << endl;

}

void main() {
	int n = 0;
	setlocale(LC_ALL, "Russian");
	int type;
	do {
		cout << "1. ������� ������� " << endl;
		cout << "2. �������� � ������� " << endl;
		cout << "3. ����� � ������� " << endl;
		cout << "4. ������� �� ������� " << endl;
		cout << "5. ������ �������" << endl;
		cout << "0. ����� " << endl;
		cout << "������� �����: " << endl;
		cin >> n;

		switch (n)
		{
		case 1:
		{
			cout << "1. TScanTable " << endl;
			cout << "2. TSortTable " << endl;
			cout << "3. THashTable " << endl;
			cout << "4. TTreeTable " << endl;
			cout << "5. TBalTree " << endl;
			cout << "������� ��� �������: " << endl;
			cin >> type;
			createTable(type);
			break;
		}
		case 2:
		{
			insertIntoTable();
			break;
		}
		case 3:
		{
			findKey();
			break;
		}
		case 4:
		{
			deleteKey();
			break;
		}
		case 5:
		{
			table->print(cout);
			break;
		}
		default:
			break;
		}
	} while (n != 0);

	
}

