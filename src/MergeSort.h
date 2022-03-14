#pragma once

#include <vector>

using namespace std;

class MergeSort
{
public:
	static void sequential(vector<unsigned int> arrayToBeSorted);
	static void parallel(vector<unsigned int> arrayToBeSorted, int cores);
	static void parallelWithThreshold(vector<unsigned int> arrayToBeSorted, int cores, int threshold);
};