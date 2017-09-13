//	Request date :	170908
//	Due date :		170911
//	Write date :	170910
//	Author : Eugene Kim aka Komastar

#include "stdafx.h"
#include "time.h"
#include <iostream>

void PrintArray(int* data);					//	Print data to console
void ShuffleArray(int* data, int loopCnt);	//	
void SelectionSort(int* data);				//	
void InsertionSort(int* data);				//	
void BubbleSort(int* data);					//	
void QuickSort(int* data, int leftIdx, int rightIdx);	//

using namespace std;

#define MAX_COUNT 10
//#define DEBUG

int main()
{
	int sampleData[MAX_COUNT];

	//	set initial data
	for (int i = 0; i < MAX_COUNT; i++)
	{
		sampleData[i] = i;
	}

	cout << "INIT COMPLETE" << endl;
	PrintArray(sampleData);

	ShuffleArray(sampleData, 10);
	PrintArray(sampleData);

	//SelectionSort(sampleData);
	//InsertionSort(sampleData);
	//BubbleSort(sampleData);
	//QuickSort(sampleData, 0, MAX_COUNT -1);

	cout << "SORT COMPLETE !!!" << endl;
	PrintArray(sampleData);

	return 0;
}

//	Print array data to console
void PrintArray(int* data)
{
	for (int i = 0; i < 10; i++)
	{
		cout << data[i] << "\t";
	}
	cout << endl;
}

//	Shuffle data
void ShuffleArray(int* data, int loopCnt)
{
	for (int i = 0; i < loopCnt; ++i)
	{
		int shuffleIdx1 = rand() % 10;
		int shuffleIdx2 = 0;
		srand(time(NULL));
		while (1)
		{
			shuffleIdx2 = rand() % 10;
			if (shuffleIdx1 != shuffleIdx2)
			{
				break;
			}
		}

		int shuffleTemp = 0;
		shuffleTemp = data[shuffleIdx1];
		data[shuffleIdx1] = data[shuffleIdx2];
		data[shuffleIdx2] = shuffleTemp;
	}

	cout << "SHUFFLED" << endl;
}

//	Selection Sort
//	http://terms.naver.com/entry.nhn?docId=2270435&cid=51173&categoryId=51173
void SelectionSort(int* data)
{
	cout << "SELECTION SORT" << endl;
	int tempIdx = 0;

	for (int i = 0; i < MAX_COUNT/*length of array*/; i++)
	{
		bool isSwitch = false;
		//	set origin data for compare
		int originNum = data[i];

		//	find target data for switch (data will be minimum)
		for (int j = i + 1; j < MAX_COUNT/*length of array*/; j++)
		{
			//	compare
			if (originNum > data[j])
			{
				tempIdx = j;
				originNum = data[j];
				isSwitch = true;
			}
		}

		//	switch data
		if (isSwitch)
		{
			int switchBuffer = data[tempIdx];
			data[tempIdx] = data[i];
			data[i] = switchBuffer;
		}
#ifdef DEBUG
		PrintArray(data);
#endif // DEBUG

	}
}

//	Insertion Sort
//	http://terms.naver.com/entry.nhn?docId=2270436&cid=51173&categoryId=51173
void InsertionSort(int* data)
{
	cout << "INSERTION SORT" << endl;
	for (int i = 1; i < MAX_COUNT; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			//	compare
			if (data[j] > data[j + 1])
			{
				//	switch data
				int temp = data[j + 1];
				data[j + 1] = data[j];
				data[j] = temp;
			}
			else
			{
#ifdef DEBUG
				PrintArray(data);
#endif // DEBUG
				break;
			}
#ifdef DEBUG
			PrintArray(data);
#endif // DEBUG
		}
	}
}

//	Bubble Sort
//	http://terms.naver.com/entry.nhn?docId=2270437&cid=51173&categoryId=51173
void BubbleSort(int* data)
{
	bool isExchange = false;

	//	loop for entire array
	for (int i = 0; i < MAX_COUNT; i++)
	{
		for (int j = 1; j < MAX_COUNT - (i + 1); j++)
		{
			if (data[j - 1] > data[j])
			{
				//	switch data
				int temp = data[j - 1];
				data[j - 1] = data[j];
				data[j] = temp;

				isExchange = true;
			}
#ifdef DEBUG
			PrintArray(data);
#endif // DEBUG
		}

		if (!isExchange)
		{
			break;
		}
#ifdef DEBUG
		cout << "---------------------------------------------" << endl;
#endif // DEBUG
	}
}

//	QuickSort
//	http://terms.naver.com/entry.nhn?docId=2270444&cid=51173&categoryId=51173
void QuickSort(int* data, int leftIdx, int rightIdx)
{
	//	first data is key
	int key = data[leftIdx];
	//	initial temp var
	int tempIdx1 = leftIdx;
	int tempIdx2 = rightIdx + 1;
	int switchTemp = 0;

	//	validate index
	if (leftIdx < rightIdx)
	{
		//	main loop
		do
		{
			//	find bigger data index than key. left to right
			while (true)
			{
				tempIdx1++;
				if (key > data[tempIdx1])
				{
					//	do nothing
				}
				else
				{
					break;
				}
			}

			//	find smaller data index than key. right to left
			while (true)
			{
				tempIdx2--;
				if (key < data[tempIdx2])
				{
					//	do nothing
				}
				else
				{
					break;
				}
			}

			if (tempIdx1 < tempIdx2)
			{
				//	switch data
				switchTemp = data[tempIdx1];
				data[tempIdx1] = data[tempIdx2];
				data[tempIdx2] = switchTemp;
			}
		} while (tempIdx1 < tempIdx2);	//	main loop end

										//	switch key data
		switchTemp = data[leftIdx];
		data[leftIdx] = data[tempIdx2];
		data[tempIdx2] = switchTemp;

#ifdef DEBUG
		PrintArray(data);
#endif // DEBUG

		QuickSort(data, leftIdx, tempIdx2 - 1);
		QuickSort(data, tempIdx2 + 1, rightIdx);
	}
}