#pragma once

#include <vector>

using namespace std;

class MergeSort
{
public:
	static void sequential(vector<unsigned int> arr);
	static void parallel(vector<unsigned int> arr, int threads);
	static void parallelWithThreshold(vector<unsigned int> arr, int threads, int threshold);
};