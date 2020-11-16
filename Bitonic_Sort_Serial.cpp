/*
 *	Bitonic_sort_Pthread_serial.c
 *
 *	Author: https://www.geeksforgeeks.org/bitonic-sort/
 *	Description: Serial implementation for bitonic sort
 */
#include "Bitonic_Sort_Serial.h"

/*The parameter dir indicates the sorting direction, ASCENDING
 or DESCENDING; if (a[i] > a[j]) agrees with the direction,
 then a[i] and a[j] are interchanged.*/
void compAndSwap(std::vector<Record> *record_vector, int i, int j, int dir) {
	if (dir == (record_vector->at(i) > record_vector->at(j)))
	{
		Record temp = record_vector->at(i);
		record_vector->at(i) = record_vector->at(j);
		record_vector->at(j)= temp;
	}
}

/*It recursively sorts a bitonic sequence in ascending order,
 if dir = 1, and in descending order otherwise (means dir=0).
 The sequence to be sorted starts at index position low,
 the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(std::vector<Record> *record_vector, int low, int cnt, int dir) {
	if (cnt > 1) {
		int k = cnt / 2;

		for (int i = low; i < low + k; i++) {
			compAndSwap(record_vector, i, i + k, dir);
		}
		bitonicMerge(record_vector, low, k, dir);
		bitonicMerge(record_vector, low + k, k, dir);
	}
}

/* This function first produces a bitonic sequence by recursively
 sorting its two halves in opposite sorting orders, and then
 calls bitonicMerge to make them in the same order */
void bitonicSort(std::vector<Record> *record_vector, int low, int cnt, int dir) {
	if (cnt > 1) {
		int k = cnt / 2;

		// sort in ascending order since dir here is 1
		bitonicSort(record_vector, low, k, 1);

		// sort in descending order since dir here is 0
		bitonicSort(record_vector, low + k, k, 0);

		// Will merge wole sequence in ascending order
		// since dir=1.
		bitonicMerge(record_vector, low, cnt, dir);
	}
}

/* Caller of bitonicSort for sorting the entire array of
 length N in ASCENDING order */
void bitonic_sort_seq(std::vector<Record> *record_vector, int N, int up) {
	bitonicSort(record_vector, 0, N, up);
}
