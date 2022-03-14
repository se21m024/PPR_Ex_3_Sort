#include "QuickSort.h"
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

int partition(vector<unsigned int> &arr, int start, int end)
{
    // Take first element as pivot element
    auto pivot = arr[start];

    // Determine index where the pivot element has to go
    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // Write pivot element on correct place
    auto pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Shift all elements smaller than the pivot element to the left and the others to the right
    int i = start;
    int j = end;

    // Go through all elements from left and right simultaneously
    while (i < pivotIndex && j > pivotIndex)
    {

        // Find first element greater than the pivot element starting from left
        while (arr[i] <= pivot)
        {
            i++;
        }

        // Find first element smaller than the pivot element starting from right
        while (arr[j] > pivot)
        {
            j--;
        }

        // Swap the two elements that were founde above
        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(vector<unsigned int> &arr, int start, int end)
{
    // Terminate recursion
    if (start >= end)
        return;

    // Partitioning the array
    auto p = partition(arr, start, end);

    // Sorting the left part
    quickSort(arr, start, p - 1);

    // Sorting the right part
    quickSort(arr, p + 1, end);
}

void parallelQuickSort(vector<unsigned int> &arr, int start, int end)
{
    if (start >= end)
        return;

    auto p = partition(arr, start, end);

#pragma omp task
    parallelQuickSort(arr, start, p - 1);
#pragma omp task
    parallelQuickSort(arr, p + 1, end);
}

void parallelThresholdQuickSort(vector<unsigned int> &arr, int start, int end, int threshold)
{
    if (start >= end)
        return;

    auto p = partition(arr, start, end);

    // Only create new tasks if threshold is not reached yet
    if (end - start > threshold)
    {
#pragma omp task
        parallelThresholdQuickSort(arr, start, p - 1, threshold);
#pragma omp task
        parallelThresholdQuickSort(arr, p + 1, end, threshold);
    }
    else
    {
        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }
}

void QuickSort::sequential(vector<unsigned int> arr)
{
    auto startTimeStamp = high_resolution_clock::now();

    quickSort(arr, 0, arr.size() - 1);

    auto stopTimeStamp = high_resolution_clock::now();
    auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
    cout << "Quicksort serial duration: " << durationMs << " ms." << endl;
}

void QuickSort::parallel(vector<unsigned int> arr, int threads)
{
    auto startTimeStamp = high_resolution_clock::now();

#pragma omp parallel
    {
#pragma omp single nowait
        parallelQuickSort(arr, 0, arr.size() - 1);
#pragma omp taskwait
    }

    auto stopTimeStamp = high_resolution_clock::now();
    auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
    cout << "Quicksort parallel with " << to_string(threads) << " threads, duration: " << to_string(durationMs) << " ms." << endl;
}

void QuickSort::parallelWithThreshold(vector<unsigned int> arr, int threads, int threshold)
{
    auto startTimeStamp = high_resolution_clock::now();

#pragma omp parallel
    {
#pragma omp single nowait
        parallelThresholdQuickSort(arr, 0, arr.size() - 1, threshold);
#pragma omp taskwait
    }

    auto stopTimeStamp = high_resolution_clock::now();
    auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
    cout << "Quicksort parallel with threshold with " << to_string(threads) << " threads, duration: " << to_string(durationMs) << " ms." << endl;
}
