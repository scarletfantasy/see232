/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name:沈瑞恩
 * Student ID:517021910873
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 */
#include"pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 2000

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

void read_file(ifstream &file_input)
{
	while (true)
	{
		cout << "filename:";
		string filename;
		cin >> filename;
		file_input.open(filename);
		if (file_input.is_open())
		{
			break;
		}
	}
	
	// TODO: your code here
}

int read_order()
{
	
	cout << "order of markov model:";
	int ordern;
	cin >> ordern;
	return ordern;
	// TODO: your code here
}

void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model)
{
	// TODO: your code here
	char ch;
	string s;
	while (file_input.get(ch))/*read the whole file as string*/
	{
		s += ch;
	}
	for (int i = 0; i < s.length() - order; ++i)
	{
		string tmp = s.substr(i, order);
		char c = s[i + order];
		if (model.count(tmp) != 0)/*check if the key exist*/
		{
			model[tmp].push_back(c);
		}
		else
		{
			vector<char> tmp1;
			tmp1.push_back(c);
			model[tmp] = tmp1;
		}
	}
	
}

void random_write(const int &order, map<string, vector<char>> &model)
{
	string max;
	map<string, vector<char>>::iterator it;
	int count = 0;
	for (it = model.begin(); it != model.end(); ++it)/*find the first string*/
	{
		if (it->second.size() > count)
		{
			max = it->first;
			count = it->second.size();
		}

	}
	cout << max;
	for (int i = 0; i < MAX_CHAR_NUM; ++i)
	{
		
		if (model.count(max) == 0)/*if no after ,end writting*/
		{
			break;
		}
				
		int rn = rand() % model[max].size();		
		
		cout << model[max][rn];/*cout the next char*/
		max = max.substr(1, order - 1) + model[max][rn];/*make the next string*/
	}
	// TODO: your code here
	
}

int main()
{
	
	// TODO: your code here
	ifstream fio;
	read_file(fio);
	int order = read_order();
	map<string, vector<char>> model;
	srand(time(NULL));
	model_read(fio, order, model);
	random_write(order, model);
	
	

	return 0;
}
