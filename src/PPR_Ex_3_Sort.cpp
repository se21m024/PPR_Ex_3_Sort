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
#include <vector>
#include <string>
#include <thread>

#include "MergeSort.cpp"
#include "QuickSort.cpp"

using namespace std::chrono;
using namespace std;

vector<unsigned int> getRandomNumbers(int arraySize)
{
	vector<unsigned int> numbers(arraySize);

	cout << "Random numbers to be sorted:" << endl;

	for (int i = 0; i < arraySize; i++)
	{
		numbers[i] = rand();
	}

	return numbers;
}

////  Note: You might need "-fopenmp" to build this project (see the example next line).
////  cd "c:\Users\tbrue\pg\c++\thomas_s\PPR_Ex_3_Sort\src\" ; if ($?) { g++ PPR_Ex_3_Sort.cpp -o PPR_Ex_3_Sort -fopenmp } ; if ($?) { .\PPR_Ex_3_Sort }

int main()
{
	int coresOnMachine = 12; // thread::hardware_concurrency();

	if (coresOnMachine < 2)
	{
		cout << "WARNING: This machine has only one core. No parallel calculation is performed! Application is shutting down." << endl;
	}
	else
	{
		const unsigned int ArraySize = 5000000;
		const int Threshold = 500000;

		auto arrayToBeSorted = getRandomNumbers(ArraySize);
		cout << endl;

		//----QUICK_SORT_SEQUENTIAL--------------------------------------------------------------------------------
		// QuickSort::sequential(arrayToBeSorted);
		//----MERGE_SORT_SEQUENTIAL--------------------------------------------------------------------------------
		// MergeSort::sequential(arrayToBeSorted);

		for (int threads = 2; threads <= coresOnMachine; threads++)
		{
			omp_set_num_threads(threads);
			//----QUICK_SORT_PARALLEL--------------------------------------------------------------------------------
			// The parallel version without threshold is very (!) slow
			// QuickSort::parallel(arrayToBeSorted, threads);
			// QuickSort::parallelWithThreshold(arrayToBeSorted, threads, Threshold);
			//----MERGE_SORT_PARALLEL--------------------------------------------------------------------------------
			// MergeSort::parallel(arrayToBeSorted, threads);
			MergeSort::parallelWithThreshold(arrayToBeSorted, threads, Threshold);
		}

		cout << endl;

		// for (int threads = 2; threads <= threadsOnMachine; threads++)
		// {
		// 	MergeSort::parallel(arrayToBeSorted, threads);
		// 	MergeSort::parallelWithThreshold(arrayToBeSorted, threads, Threshold);
		// }

		cout << endl;

		// for (int i = 0; i < arrayToBeSorted.size(); ++i)
		// {
		// 	cout << arrayToBeSorted[i] << ' ';
		// }
	}

	cin.get();

	return 0;
}
