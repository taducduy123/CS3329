#ifndef	 BUCKETSORT_H
#define	 BUCKETSORT_H
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int findMaxValue(int set[], int size)
{
	int max = set[0];
	for(int i = 1; i < size; i++)
	{
		if(set[i] > max)
		{
			max = set[i];
		}
	}
	return max;
}

int findMinValue(int set[], int size)
{
	int min = set[0];
	for(int i = 1; i < size; i++)
	{
		if(set[i] < min)
		{
			min = set[i];
		}
	}
	return min;
}

int findNumberOfDigits(int number)
{
	int numDigits = 1;
	while(abs(number) >= pow(10, numDigits))								//# Comparisons = m
	{
		numDigits++;
	}
	return numDigits;
}

int findMaxNumDigits(int set[], int size)
{
	int maxValue = findMaxValue(set, size);									//# Comparisons = 2n-1
	return findNumberOfDigits(maxValue);									//# Comparisons = m
}

void BucketSort(int set[], int size)
{
	//1. Create several buckets
	int minValue = findMinValue(set, size);
	int maxValue = findMaxValue(set, size);
	int numBuckets = maxValue - minValue + 1;
	vector<int> buckets[numBuckets];
	//2. Push elements in the list to corresponding buckets
	for(int i = 0; i < size; i++)
	{
		buckets[set[i] - minValue].push_back(set[i]);
	}
	//3. Collect elements from buckets
	int k = 0;
	for(int i = 0; i < numBuckets; i++)
	{
		for(int j = 0; j < buckets[i].size(); j++)
		{
			set[k] = buckets[i][j];
			k++;
		}
	}
}

void BucketSort(int set[], int size, int d)
{
	int maxNumDigits = findMaxNumDigits(set, size);							//# Comparisons = (2n+m-1)
	int digits[size];
	if(d <= maxNumDigits)													//# Comparisons = 1
	{
		//Collect the digit at d-th position of each number
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			digits[i] = (set[i] % ((int)pow(10, d))) / ((int)pow(10, d-1));
		}
	}
	else
	{
		//Collect the sign of each number									
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			if(set[i] >= 0)													//# Comparisons = n
				digits[i] = 1;		//positive
			else
				digits[i] = 0;		//negative
		}
	}
	
	//1. Create several buckets
	int minValue = findMinValue(digits, size);
	int maxValue = findMaxValue(digits, size);
	int numBuckets = maxValue - minValue + 1;
	vector<int> buckets[numBuckets];
	//2. Push elements in the list to corresponding buckets
	for(int i = 0; i < size; i++)
	{
		buckets[digits[i] - minValue].push_back(set[i]);
	}
	//3. Collect elements from buckets
	int k = 0;
	for(int i = 0; i < numBuckets; i++)
	{
		for(int j = 0; j < buckets[i].size(); j++)
		{
			set[k] = buckets[i][j];
			k++;
		}
	}
}

#endif
