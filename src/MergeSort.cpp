#include "MergeSort.h"
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <string>
#include <thread>

using namespace std::chrono;
using namespace std;

void mergeSortedIntervals(vector<unsigned int> &v, int s, int m, int e)
{

	vector<unsigned int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e)
	{

		if (v[i] <= v[j])
		{
			temp.push_back(v[i]);
			++i;
		}
		else
		{
			temp.push_back(v[j]);
			++j;
		}
	}

	while (i <= m)
	{
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e)
	{
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];
}

void mergeSort(vector<unsigned int> &v, int s, int e)
{
	if (s < e)
	{
		int m = (s + e) / 2;
		mergeSort(v, s, m);
		mergeSort(v, m + 1, e);
		mergeSortedIntervals(v, s, m, e);
	}
}

void parallelMergeSort(vector<unsigned int> &v, int s, int e)
{
	if (s < e)
	{
		int m = (s + e) / 2;
#pragma omp task
		mergeSort(v, s, m);
#pragma omp task
		mergeSort(v, m + 1, e);
		mergeSortedIntervals(v, s, m, e);
	}
}

void parallelThresholdMergeSort(vector<unsigned int> &v, int s, int e, int threshold)
{

	if (s < e)
	{

		if (e - s > threshold)
		{

			int m = (s + e) / 2;
#pragma omp task
			parallelThresholdMergeSort(v, s, m, threshold);
#pragma omp task
			parallelThresholdMergeSort(v, m + 1, e, threshold);
			mergeSortedIntervals(v, s, m, e);
		}
		else
		{
			int m = (s + e) / 2;
			mergeSort(v, s, m);
			mergeSort(v, m + 1, e);
			mergeSortedIntervals(v, s, m, e);
		}
	}
}

void MergeSort::sequential(vector<unsigned int> arr)
{

	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array
	mergeSort(arr, 0, arr.size() - 1);

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "MergeSort serial duration: " << durationMs << " ms." << endl;
}

void MergeSort::parallel(vector<unsigned int> arr, int threads)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

#pragma omp parallel
	{
#pragma omp single nowait
		parallelMergeSort(arr, 0, arr.size() - 1);
#pragma omp taskwait
	}

	// 	#pragma omp parallel
	//     {
	// #pragma omp single nowait
	//         parallelQuickSort(arr, 0, arr.size() - 1);
	// #pragma omp taskwait
	//     }

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "MergeSort parallel with " << to_string(threads) << " threads, duration: " << to_string(durationMs) << " ms." << endl;
}

void MergeSort::parallelWithThreshold(vector<unsigned int> arr, int threads, int threshold)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

#pragma omp parallel
	{
#pragma omp single nowait
		parallelThresholdMergeSort(arr, 0, arr.size() - 1, threshold);
#pragma omp taskwait
	}

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "MergeSort parallel with threshold with " << to_string(threads) << " threads, duration: " << to_string(durationMs) << " ms." << endl;
}
