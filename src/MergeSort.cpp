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

void MergeSort::sequential(vector<unsigned int> arr)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "MergeSort serial duration: " << durationMs << " ms." << endl;
}

void MergeSort::parallel(vector<unsigned int> arr, int cores)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "MergeSort parallel with " << to_string(cores) << " cores, duration: " << to_string(durationMs) << " ms." << endl;
}

void MergeSort::parallelWithThreshold(vector<unsigned int> arr, int cores, int threshold)
{
	auto startTimeStamp = high_resolution_clock::now();

	// Todo: Sort array

	auto stopTimeStamp = high_resolution_clock::now();
	auto durationMs = duration_cast<microseconds>(stopTimeStamp - startTimeStamp).count() / 1000;
	cout << "MergeSort parallel with threshold with " << to_string(cores) << " cores, duration: " << to_string(durationMs) << " ms." << endl;
}