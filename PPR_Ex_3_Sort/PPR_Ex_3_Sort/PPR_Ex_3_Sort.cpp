/*
	Parallel Programming
	Exercise 3
	Sorting Algorithms

	Student 1: Thomas Bründl
	Student 2: Thomas Stummer
*/

#include "QuickSort.h"
#include "MergeSort.h"
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <ostream>
#include <chrono>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <thread>

using namespace std::chrono;
using namespace std;

vector<unsigned int> GetRandomNumbers(int arraySize)
{
	vector<unsigned int> numbers(arraySize);

	cout << "Random numbers to be sorted:" << endl;

	for (int i = 0; i < arraySize; i++)
	{
		numbers[i] = rand();
		cout << "#" << to_string(i) << ": " << to_string(numbers[i]) << endl;
	}

	return numbers;
}

int main()
{
	int coresOnMachine = 3; // thread::hardware_concurrency();

	if (coresOnMachine < 2)
	{
		cout << "WARNING: This machine has only one core. No parallel calculation is performed! Application is shutting down." << endl;
	}
	else
	{
		const int ArraySize = 10;
		const int Threshold = 3;

		auto arrayToBeSorted = GetRandomNumbers(ArraySize);
		cout << endl;

		QuickSort::Sequential(arrayToBeSorted);

		for (int cores = 2; cores <= coresOnMachine; cores++)
		{	
			QuickSort::Parallel(arrayToBeSorted, cores);
			QuickSort::ParallelWithThreshold(arrayToBeSorted, cores, Threshold);
		}

		cout << endl;

		MergeSort::Sequential(arrayToBeSorted);

		for (int cores = 2; cores <= coresOnMachine; cores++)
		{
			MergeSort::Parallel(arrayToBeSorted, cores);
			MergeSort::ParallelWithThreshold(arrayToBeSorted, cores, Threshold);
		}
	}

	return 0;
}

