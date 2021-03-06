/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name:517021910873
 * Student ID:
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(set<string> &english);

bool canchange(string&, string&);/*check if two words can make a ladder*/


void show_ans(vector<string> &ans)
{
	cout << "Found ladder:";
	cout << ans[0];
	for (int i = 1; i < ans.size(); i++)
	{
		cout << "->" << ans[i];
	}
	cout << endl
		<< endl;
}

void input_words(string &start, string &dest)
{
	cout << "Enter start word (enter ':q' to quit):";
	cin >> start;
	if (start == ":q")
	{
		exit(0);
	}
	cout << "Enter destination word:";
	cin >> dest;
}

void read_english(set<string> &english)
{
	while (true)
	{
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		ifstream file_input(file_name.c_str());
		if (file_input.is_open())
		{
			string temp_word;
			while (getline(file_input, temp_word))
			{
				english.insert(temp_word);
			}
			break;
		}
	}
}

int main()
{
	// TODO: your code
	while (cin)
	{
		set<string> word;
		read_english(word);
		queue<vector<string>> all;

		string begin_word, end_word;
		input_words(begin_word, end_word);


		vector<string> a;
		a.push_back(begin_word);
		vector<string> exist;
		vector<string> result;
		all.push(a);
		bool find = false;
		vector<string>::iterator it;
		set<string>::iterator itw;
		set<string> word_n;
		int wordlen = begin_word.length();
		if (begin_word.length() != end_word.length())
		{
			cout << "no ladder exists" << '\n';
				continue;
		}
		for (itw = word.begin(); itw != word.end(); ++itw)/*select the word has the same length*/
		{
			if (itw->length() == wordlen)
				word_n.insert(*itw);
		}
		exist.push_back(begin_word);		
		while (!all.empty())
		{
			vector<string> tmp = all.front();/*pop a ladder*/
			string tmps = tmp[tmp.size() - 1];
			if (tmps == end_word)
			{

				find = true;
				break;
			}
			all.pop();
			
			for (itw = word_n.begin(); itw != word_n.end(); ++itw)
			{
				string tmpw = *itw;
				if (canchange(tmps, tmpw))/*two words can make a ladder*/
				{
					if (tmpw == end_word)
					{
						result = tmp;
						result.push_back(end_word);
						find = true;
					}
					
					
					if (count(exist.begin(),exist.end(),tmpw)==0)/*current word isnot exist in the  last word*/
					{
						vector<string> tmp1 = tmp;
						exist.push_back(tmpw);
						tmp1.push_back(tmpw);
						all.push(tmp1);
					}
				}
				if (find)
				{
					break;
				}
			}
			if (find)
			{
				break;
			}


		}
		if (find)
		{
			show_ans(result);
		}
		else
		{
			cout << "no ladder exists" << '\n';
		}
	}


	return 0;
}
inline bool canchange(string &a, string &b)
{
	if (a.length() != b.length())
	{
		return false;
	}
	else
	{
		int i = 0;
		for (int j = 0; j < a.length(); ++j)
		{
			if (a[j] != b[j])
			{
				++i;
			}
		}
		if (i == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
