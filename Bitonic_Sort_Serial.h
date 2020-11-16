/*
 * Bitonic_Sort_Serial.h
 *
 *  Created on: Oct 11, 2020
 *      Author: nick
 */

#ifndef BITONIC_SORT_SERIAL_H_
#define BITONIC_SORT_SERIAL_H_

#include "file_reader.h"

void compAndSwap(std::vector<Record> *record_vector, int i, int j, int dir);
void bitonicMerge(std::vector<Record> *record_vector, int low, int cnt, int dir);
void bitonicSort(std::vector<Record> *record_vector, int low, int cnt, int dir);
void bitonic_sort_seq(std::vector<Record> *record_vector, int N, int up);


#endif /* BITONIC_SORT_SERIAL_H_ */
