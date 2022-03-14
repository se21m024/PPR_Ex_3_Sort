#pragma once

#include <vector>

using namespace std;

class QuickSort
{
public:
	static void sequential(vector<unsigned int> arrayToBeSorted);
	static void parallel(vector<unsigned int> arrayToBeSorted, int threads);
	static void parallelWithThreshold(vector<unsigned int> arrayToBeSorted, int threads, int threshold);
};