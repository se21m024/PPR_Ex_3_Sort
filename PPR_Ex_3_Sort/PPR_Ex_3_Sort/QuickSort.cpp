#include "QuickSort.h"
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

int partition(vector<unsigned int> &arr, int start, int end)
{
    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(vector<unsigned int> &arr, int start, int end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quickSort(arr, start, p - 1);

    // Sorting the right part
    quickSort(arr, p + 1, end);
}

void QuickSort::Sequential(vector<unsigned int> arr)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

    quickSort(arr, 0, arr.size() - 1);

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "Quicksort serial duration: " << durationMs << " ms." << endl;

    // Print sorted array
    for (int i = 0; i < arr.size(); i++)
    {
        cout << "#" << to_string(i) << ": " << to_string(arr[i]) << endl;
    }
}

void QuickSort::Parallel(vector<unsigned int> arr, int cores)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "Quicksort parallel with " << to_string(cores) << " cores, duration: " << to_string(durationMs) << " ms." << endl;
}

void QuickSort::ParallelWithThreshold(vector<unsigned int> arr, int cores, int threshold)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "Quicksort parallel with threshold with " << to_string(cores) << " cores, duration: " << to_string(durationMs) << " ms." << endl;
}
