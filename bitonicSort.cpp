/*********************************************
 * PBNS - OpenMP version
 * Original OpenMP implementation from https://github.com/richursa/cpuBitonicSort
 * Author: richu shaji abraham richursa
 *
 * PBNS modified to sort KDS raw data
 * Authors: John M., Nicholas B., Coby F.
 *
 *********************************************/

#include<iostream>
#include<omp.h>
#include <sys/time.h>
#include <vector>
#include "file_reader.h"
using namespace std;

#define RMAX 100
vector<Record> *llc_file_vector;

// int *array Version
//
void ascendingSwap(int index1 , int index2 , int *ar) { //swap two values such that they appear in ascending order in the array
	if(ar[index2] < ar[index1]) {
		int temp = ar[index2];
		ar[index2] = ar[index1];
		ar[index1] = temp;
	}
}

// vector<Record> *records version
//
void ascendingSwap(int index1 , int index2 , vector<Record> *records) { //swap two values such that they appear in ascending order in the array
	if(records->at(index2).dLoan < records->at(index1).dLoan) {
		Record temp = records->at(index2);
		records->at(index2) = records->at(index1);
		records->at(index1) = temp;
	}
}

// int *array Version
//
void decendingSwap(int index1 , int index2 , int *ar) { //swap two values such that they appear in decending order in the array
	if(ar[index1] < ar[index2]) {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
	}
}

// vector<Record> *records Version
//
void decendingSwap(int index1 , int index2 , vector<Record> *records) { //swap two values such that they appear in decending order in the array
	if(records->at(index1).dLoan < records->at(index2).dLoan) {
		Record temp = records->at(index2);
		records->at(index2) = records->at(index1);
		records->at(index1) = temp;
	}
}

// int *array Version
//
void bitonicSortFromBitonicSequence( int startIndex ,int lastIndex, int dir , int *ar ) {    //form a increaseing or decreasing array when a bitonic input is given to the function
	if(dir == 1) {
		int counter = 0;                                                                    //counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
		int noOfElements = lastIndex - startIndex + 1;
		for(int j = noOfElements/2;j>0;j = j/2) {
			counter =0;
			for(int i = startIndex ; i +j <= lastIndex ; i++) {
				if(counter < j) {
					ascendingSwap(i,i+j,ar);
					counter++;
				}
				else {
					counter =0;
					i = i+ j-1;
				}
			}
		}
	}
	else { //Descending sort
		int counter = 0;
		int noOfElements = lastIndex - startIndex + 1;
		for(int j = noOfElements/2;j>0;j = j/2) {
			counter =0;
			for(int i = startIndex ; i <= (lastIndex-j) ; i++) {
				if(counter < j) {
					decendingSwap(i,i+j,ar);
					counter++;
				}
				else {
					counter =0;
					i = i+ j-1;
				}
			}
		}
	}
}

// vector<Record> *records Version
//
void bitonicSortFromBitonicSequence( int startIndex ,int lastIndex, int dir , vector<Record> *records ) {    //form a increaseing or decreasing array when a bitonic input is given to the function
	if(dir == 1) {
		int counter = 0; //counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
		int noOfElements = lastIndex - startIndex + 1;
		for(int j = noOfElements/2;j>0;j = j/2) {
			counter =0;
			for(int i = startIndex ; i +j <= lastIndex ; i++) {
				if(counter < j) {
					ascendingSwap(i,i+j,records);
					counter++;
				}
				else {
					counter =0;
					i = i+ j-1;
				}
			}
		}
	}
	else { //Descending sort
		int counter = 0;
		int noOfElements = lastIndex - startIndex + 1;
		for(int j = noOfElements/2;j>0;j = j/2) {
			counter =0;
			for(int i = startIndex ; i <= (lastIndex-j) ; i++) {
				if(counter < j) {
					decendingSwap(i,i+j,records);
					counter++;
				}
				else {
					counter =0;
					i = i+ j-1;
				}
			}
		}
	}
}

// int *array Version
//
void bitonicSequenceGenerator(int startIndex , int lastIndex , int *ar) { //generate a bitonic sequence  from a a random order
	int noOfElements = lastIndex - startIndex +1;
	for(int j = 2;j<=noOfElements;j = j*2) {
		#pragma omp parallel for  //parallel implementation results in most performance gains here
		for(int i=0;i<noOfElements;i=i+j) {
			if(((i/j)%2) ==0) { //extra computation results in drastically lower performance ,need to fix
				bitonicSortFromBitonicSequence(i,i+j-1,1,ar);
			}
			else {
				bitonicSortFromBitonicSequence(i,i+j-1,0,ar);
			}
		}
	}
}

// vector<Record> *records Version
//
void bitonicSequenceGenerator(int startIndex , int lastIndex , vector<Record> *records) { //generate a bitonic sequence  from a a random order
	int noOfElements = lastIndex - startIndex +1;
	for(int j = 2;j<=noOfElements;j = j*2) {
		#pragma omp parallel for  //parallel implementation results in most performance gains here
		for(int i=0;i<noOfElements;i=i+j) {
			if(((i/j)%2) ==0) { //extra computation results in drastically lower performance ,need to fix
				bitonicSortFromBitonicSequence(i,i+j-1,1,records);
			}
			else {
				bitonicSortFromBitonicSequence(i,i+j-1,0,records);
			}
		}
	}
}

int getNextPowerOf2(int size) {
	unsigned count = 0;
	int newSize = size;
	if (size && !(size & (size - 1))) {
		printf("Input is a power of 2: %d", size);
		return size;
	}
	while (size != 0) {
		size >>= 1;
		count += 1;
	}
	newSize = 1 << count;
	return newSize;
}

// int *array Version
//
void paddArray(int *array, int originalSize, int newSize) {
	srand(time(NULL));
	for (int i = 0; i < originalSize; i++) {
		// Fill with random integers
		//
		array[i] = rand() % RMAX;
	}

	for (int i = originalSize; i < newSize; i++) {
		// Pad with dummy records
		//
		array[i] = -1;
	}
}

// vector<Record> *records Version
//
void paddVector(vector<Record> *records, int originalSize, int newSize) {
	int difference = newSize - originalSize;

	for(int i = 0; i < difference; i++){
		Record temp;
		temp.makeDummyRecord();
		records->push_back(temp);
	}
}

void Gen_list(int list[], int size, int newSize) {
	paddArray(list, size, newSize);
}

int main() 													//main driver function
{   
	struct timeval start, end; 								//Timers
    omp_set_dynamic(0); 									//disabled so that the os doesnt override the thread settings
    int maxNumberOfThreads = omp_get_num_procs(); 			//gives number of logical cores
    omp_set_num_threads(maxNumberOfThreads); 				//set the no of threads

    // start timer
    //
    gettimeofday(&start, NULL);

	vector<Record> tempVector = fileToVector("llc_fnll_202003");
	// get time
	//
	gettimeofday(&end, NULL);
	printf("Read input file in %f seconds\n",
			(double) (end.tv_sec - start.tv_sec)
					+ (double) (end.tv_usec - start.tv_usec) / 1000000);

	int originalSize = tempVector.size();
    int newSize = getNextPowerOf2(originalSize);
	llc_file_vector = &tempVector;
    paddVector(llc_file_vector, originalSize, newSize);


	printf("Done reading file...\n");
    printf("Input size: %d\n", originalSize);
    printf("Size with dummy records: %d\n", llc_file_vector->size());
    printf("Number of threads: %d\n", maxNumberOfThreads);
    // start timer
    //
    gettimeofday(&start, NULL);
    // Sort
    //
    //bitonicSequenceGenerator(0,newSize-1,ar);
    bitonicSequenceGenerator(0,llc_file_vector->size() - 1,llc_file_vector);
	// get time
	//
	gettimeofday(&end, NULL);
	printf("Time to sort = %f seconds\n",
			(double) (end.tv_sec - start.tv_sec)
					+ (double) (end.tv_usec - start.tv_usec) / 1000000);


    // Print out sorted array to file
    // start timer
    //
    gettimeofday(&start, NULL);
	ofstream myfile;
	myfile.open ("sorted-records.txt");

    for(int i = 0;i < llc_file_vector->size();i++)
    {
        myfile << llc_file_vector->at(i) << endl;
    }

	myfile.close();
	// get time
	//
	gettimeofday(&end, NULL);
	printf("Wrote Sorted Records to file in %f seconds\n",
			(double) (end.tv_sec - start.tv_sec)
					+ (double) (end.tv_usec - start.tv_usec) / 1000000);

}

