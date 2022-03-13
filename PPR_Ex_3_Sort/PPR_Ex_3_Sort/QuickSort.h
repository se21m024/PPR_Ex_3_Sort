#pragma once

#include <vector>

using namespace std;

class QuickSort
{
public:
	static void Sequential(vector<unsigned int> arrayToBeSorted);
	static void Parallel(vector<unsigned int> arrayToBeSorted, int cores);
	static void ParallelWithThreshold(vector<unsigned int> arrayToBeSorted, int cores, int threshold);
};