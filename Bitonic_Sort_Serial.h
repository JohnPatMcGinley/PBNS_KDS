/*
 * Bitonic_Sort_Serial.h
 *
 *  Created on: Oct 11, 2020
 *      Author: nick
 */

#ifndef BITONIC_SORT_SERIAL_H_
#define BITONIC_SORT_SERIAL_H_


void compAndSwap(int a[], int i, int j, int dir);
void bitonicMerge(int a[], int low, int cnt, int dir);
void bitonicSort(int a[], int low, int cnt, int dir);
void bitonic_sort_seq(int a[], int N, int up);


#endif /* BITONIC_SORT_SERIAL_H_ */
