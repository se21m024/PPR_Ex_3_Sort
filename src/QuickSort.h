#pragma once

#include <vector>

using namespace std;

class QuickSort
{
public:
	static void sequential(vector<unsigned int> arr);
	static void parallel(vector<unsigned int> arr, int threads);
	static void parallelWithThreshold(vector<unsigned int> arr, int threads, int threshold);
};