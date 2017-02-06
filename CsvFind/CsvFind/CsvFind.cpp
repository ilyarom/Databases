// CsvFind.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;


void SplitLine(string &line, vector <string> &name, vector <string> &id)
{
	// сделал этот велосипед т.к. не уверен, можно ли использовать более упрощенные функции поиска
	string element = "";
	int numOfField = 0;
	for (int i = 0; i < line.length(); ++i)
	{
		if (line[i] == '"')
		{
			continue;
		}
		if (line[i] == ',')
		{
			if (numOfField == 0)
			{
				id.push_back(element);
			}
			else if (numOfField == 4)
			{
				name.push_back(element);
			}
			++numOfField;
			element = "";
		}
		else
		{
			element += line[i];
		}
	}
}

void ReadCsvData(ifstream &file, vector <string> &name, vector <string> &id)
{
	string line;
	file >> line; // считываем заголовочную строку
	while (getline(file, line))
	{
		SplitLine(line, name, id);
	}
}

void HandleData(string soughtName, vector <string> &name, vector <string> &id)
{
	for (int i = 0; i < name.size(); ++i)
	{
		if (name[i] == soughtName)
		{
			cout << id[i] << ", ";
		}
	}
}

int main()
{
	ifstream file("db.csv");
	vector <string> name;
	vector <string> id;
	string soughtName;
	cout << "Enter username: ";
	getline(cin, soughtName);
	ReadCsvData(file, name, id);
	cout << "Record id: ";
	HandleData(soughtName, name, id);
	cout << endl;
    return 0;
}

