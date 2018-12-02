// hw12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
/*
 * File Heap.h
 * -----------
 * You should finish your homework in this file
 */

#ifndef _heap_h
#define _heap_h

#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
 * Class Heap
 * ----------
 * This is the class you should implement.
 * It is a template class, Compare can be greater<int>, less<int> and so on.
 * When you define a Heap like Heap<greater<int>>, it should be a maxHeap (who's top this the max element)
 * When you define a Heap like Heap<less<int>>, it should be a minHeap (who's top this the min element)
 * So, when you want to compare two element while implement the member function, you shoud use the member variable cmp, rather than <,<=,>,>=
 */
template<class Compare>
class Heap
{
private:
	// use elements to store the element
	map<int, vector<int>> elements;

	// cmp is a comparer that can help you to compare two element's priority
	// Usage:
	// cmp(element_1, element_2)
	// if element_1's priority is higher than element_2, it will return true, otherwise, return false
	// Example:
	// when you define a Heap like Heap<greater<int>>, it means Compare is greater<int>, and cmp is a instance of greater<int>
	// So, cmp(1,2) and cmp(1,1) will return false and cmp(2,1) will return true
	// when you define a Heap like Heap<less<int>>, it means Compare is less<int>, and cmp is a instance of less<int>
	// So, cmp(2,1) and cmp(1,1) will return false and cmp(1,2) will return true
	// By this way, you can implement minHeap and maxHeap using one class
	Compare cmp;

	// the Top element's index, can make the code more readable
	// It's up to you whether to use it
	// pair<int,int> topIndex = make_pair(0,0);

	// Some help function, can improve the code structure
	// It's up to you whether to use them
	// pair<int,int> getParentIndex(pair<int,int> index);
	// pair<int,int> getLeftIndex(pair<int,int> index);
	// pair<int,int> getRightIndex(pair<int,int> index);
	// bool isInRange(pair<int,int> index);
	// bool isTop(pair<int,int> index);
	// void swap(pair<int,int> index_1, pair<int,int> index_2);
	// pair<int,int> findIndex(int element);
	// void shift_up(pair<int,int> index);
	// void shift_down(pair<int,int> index);

public:
	pair<int, int> getParentIndex(pair<int, int> index)
	{
		return(pair<int, int>(index.first - 1, index.second / 2));
	}
	
	pair<int, int> getLeftIndex(pair<int, int> index)
	{
		return(pair<int, int>(index.first + 1, index.second * 2));
	}
	pair<int, int> getRightIndex(pair<int, int> index)
	{
		return(pair<int, int>(index.first + 1, index.second * 2+1));
	}
	bool isTop(pair<int, int> index)
	{
		return(index.first == 0);
	}
	bool isInRange(pair<int, int> index)
	{
		return index.first >= 0 && index.first < (elements.size()-1) || index.first == (elements.size() - 1)&&index.second < elements[elements.size() - 1].size();
	}
	void shift_up(pair<int, int> index)
	{
		while (index.first != 0)
		{
			auto tmp = getParentIndex(index);
			if (cmp(elements[index.first][index.second], elements[tmp.first][tmp.second]))
			{
				swap(index, tmp);
				index = tmp;
			}
			else
				break;
		}
	}
	void shift_down(pair<int, int> index)
	{
		while (true)
		{
			auto left = getLeftIndex(index);
			auto right = getRightIndex(index);
			if (isInRange(right))
			{
				if (cmp(elements[right.first][right.second], elements[left.first][left.second]))
				{
					if (cmp(elements[right.first][right.second], elements[index.first][index.second]))
					{
						swap(index, right);
						index = right;
					}
					else
						break;
				}
				else if (cmp(elements[left.first][left.second], elements[index.first][index.second]))
				{
					swap(index, left);
					index = left;
				}
				else
					break;
			}
			else if (isInRange(left))
			{
				if (cmp(elements[left.first][left.second], elements[index.first][index.second]))
				{
					swap(index, left);
					index = left;
				}
				else
					break;
			}
			else
				break;
		}
	}
	void swap(pair<int, int> index_1, pair<int, int> index_2)
	{
		int tmp = elements[index_1.first][index_1.second];
		elements[index_1.first][index_1.second] = elements[index_2.first][index_2.second];
		elements[index_2.first][ index_2.second] = tmp;
	}
	/*
	 * Constructor: Heap()
	 * Usage: Heap<greater<int>> maxHeap
	 */
	Heap();

	/*
	 * Constructor: Heap(vector<int> init_elements)
	 * Usage: Heap<greater<int>> maxHeap(init_elements)
	 * ------------------------------------------------
	 * You should implement this Method with O(mlog(n)) time complexity (m = init_elements.size(), n = elements.size())
	 */
	Heap(vector<int> init_elements);

	/*
	 * Destructor: ~Heap()
	 * Usage: usually implicit
	 */
	~Heap();

	/*
	 * Method: insert(int element)
	 * Usage: maxHeap.insert(1)
	 * ------------------------
	 * Add the new element in to the end of elements and shift_up this element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	void insert(int element);

	/*
	 * Method: insert(vector<int> new_elements)
	 * Usage: maxHeap.insert(new_elements)
	 * ------------------------
	 * Add the new element in to the end of elements and shift_up this element one by one
	 * You should implement this Method with O(mlog(n)) time complexity (m = new_elements.size(), n = elements.size())
	 */
	void insert(vector<int> new_elements);

	/*
	 * Method: erase(int element)
	 * Usage: maxHeap.erase(1)
	 * ------------------------
	 * Swap this element with the elements's last element, delete the last element, and shift_down the swapped element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	bool erase(int element);

	/*
	 * Method: pop()
	 * Usage: maxHeap.pop()
	 * ------------------------
	 * Swap the top element with the elements's last element, delete and return the last element, and shift_down the swapped element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	int pop();

	/*
	 * Method: top()
	 * Usage: maxHeap.top()
	 * ------------------------
	 * return the top element
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int top();

	/*
	 * Method: size()
	 * Usage: maxHeap.size()
	 * ------------------------
	 * return the number of element in the Heap
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int size();
};

template<class Compare>
Heap<Compare>::Heap()
{
	// you code here
}

template<class Compare>
Heap<Compare>::~Heap()
{
	// you code here
}

template<class Compare>
Heap<Compare>::Heap(vector<int> init_elements)
{
	int n = init_elements.size();
	
	for (int i = 0; i < n; ++i)
	{
		insert(init_elements[i]);
	}

	// you code here
}

template<class Compare>
void Heap<Compare>::insert(int element)
{
	
	// you code here
	int s = elements.size();
	int n = pow(2, s - 1);
	pair<int, int> a;
	if (s == 0)
	{
		elements[s].push_back(element);
		a = pair<int, int>(s, 0);
	}
	else if (elements[s - 1].size() == n)
	{
		elements[s].push_back(element);
		a = pair<int, int>(s, 0);
	}
	else
	{
		elements[s-1].push_back(element);
		a = pair<int, int>(s-1, elements[s - 1].size()-1);
	}
	shift_up(a);
}

template<class Compare>
void Heap<Compare>::insert(vector<int> new_elements)
{
	int n = new_elements.size();
	for (int i = 0; i < n; ++i)
	{
		insert(new_elements[i]);
	}
	// you code here
}

template<class Compare>
bool Heap<Compare>::erase(int element)
{
	
	
	for ( int i = 0; i < elements.size(); ++i)
	{
		for ( int j = 0; j < elements[i].size(); ++j)
		{
			if (elements[i][j] == element)
			{
				pair<int, int>  now(i,j),end(elements.size() - 1, elements[elements.size() - 1].size() - 1);
				swap(now, end);
				elements[elements.size() - 1].pop_back();
				shift_down(now);
				shift_up(now);
				return true;
			}
		}
	}
	return false;
	// you code here
}

template<class Compare>
int Heap<Compare>::pop()
{
	int x = top();
	pair<int, int> top(0, 0),end(elements.size()-1,elements[elements.size() - 1].size()-1);
	swap(top, end);
	
	elements[elements.size() - 1].pop_back();
	shift_down(top);
	return x;
	
	// you code here
}

template<class Compare>
int Heap<Compare>::top()
{
	return elements[0][0];
	// you code here
}

template<class Compare>
int Heap<Compare>::size()
{
	return pow(2, elements.size() - 1)-1 + elements[elements.size() - 1].size();
	// you code here
}

#endif

int main()
{
	int total_score = 100;
	int score = 0;
	vector<int> init_elements = { 4, 7, 3, 5, 9, 21, 33, 6, 10, 16 };
	vector<int> new_elements = { 5, 1, 45 };

	// maxHeap init test
	Heap<greater<int>> maxHeap(init_elements);
	if (maxHeap.size() == 10 && maxHeap.top() == 33)
	{
		printf("%-24s%s\n", "MaxHeap Create", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MaxHeap Create", "Failed");
	}

	// maxHeap singleInsert test
	maxHeap.insert(21);
	maxHeap.insert(43);
	if (maxHeap.size() == 12 && maxHeap.top() == 43)
	{
		printf("%-24s%s\n", "MaxHeap SingleInsert", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MaxHeap SingleInsert", "Failed");
	}

	// maxHeap multiInsert test
	maxHeap.insert(new_elements);
	if (maxHeap.size() == 15 && maxHeap.top() == 45)
	{
		printf("%-24s%s\n", "MaxHeap MultiInsert", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MaxHeap MultiInsert", "Failed");
	}

	// maxHeap pop test
	if (maxHeap.pop() == 45 && maxHeap.pop() == 43 && maxHeap.pop() == 33 && maxHeap.size() == 12 && maxHeap.top() == 21)
	{
		printf("%-24s%s\n", "MaxHeap Pop", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MaxHeap Pop", "Failed");
	}

	// maxHeap erase test
	maxHeap.erase(16);
	if (maxHeap.size() == 11 && maxHeap.pop() == 21 && maxHeap.pop() == 21 && maxHeap.top() == 10)
	{
		printf("%-24s%s\n", "MaxHeap Erase", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MaxHeap Erase", "Failed");
	}

	// minHeap init test
	Heap<less<int>> minHeap(init_elements);
	if (minHeap.size() == 10 && minHeap.top() == 3)
	{
		printf("%-24s%s\n", "MinHeap Create", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MinHeap Create", "Failed");
	}

	// minHeap singleInsert test
	minHeap.insert(21);
	minHeap.insert(2);
	if (minHeap.size() == 12 && minHeap.top() == 2)
	{
		printf("%-24s%s\n", "MinHeap SingleInsert", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MinHeap SingleInsert", "Failed");
	}

	// minHeap multiInsert test
	minHeap.insert(new_elements);
	if (minHeap.size() == 15 && minHeap.top() == 1)
	{
		printf("%-24s%s\n", "MinHeap MultiInsert", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MinHeap MultiInsert", "Failed");
	}

	// minHeap pop test
	if (minHeap.pop() == 1 && minHeap.pop() == 2 && minHeap.pop() == 3 && minHeap.size() == 12 && minHeap.top() == 4)
	{
		printf("%-24s%s\n", "MinHeap Pop", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MinHeap Pop", "Failed");
	}

	// minHeap erase test
	minHeap.erase(5);
	if (minHeap.size() == 11 && minHeap.pop() == 4 && minHeap.pop() == 5 && minHeap.top() == 6)
	{
		printf("%-24s%s\n", "MinHeap Erase", "Pass");
		score += 10;
	}
	else
	{
		printf("%-24s%s\n", "MinHeap Erase", "Failed");
	}

	printf("%-24s%d/%d\n", "Total Score", score, total_score);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
