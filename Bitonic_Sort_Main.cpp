/* File:     pth_bitonic.c
 *
 * Original Author:   https://www.csee.umbc.edu/~tsimo1/CMSC483/cs220/code/sorting/pth_bitonic.c
 *
 * Purpose:  Implement bitonic sort of a list of ints using Pthreads
 *
 * Compile:  gcc -g -Wall -o pth_bitonic pth_bitonic.c -lpthread
 * Run:      ./pth_bitonic <thread count> <n> [g] [o]
 *           n = number of ints in the list
 *           If 'g' is included on the command line, the program
 *              will use a random number generator to generate
 *              the list to be sorted.
 *           If 'o' is included on the command line, the program
 *              will print the original list and the sorted list
 *
 * Input:    If 'g' is not on the command line, user should enter
 *           the elements of the list
 *
 * Output:   If 'o' is included on the command line, the original
 *           list and the sorted list.
 *           The elapsed time for the sort.
 *
 * Notes:
 * 1.  thread_count should be a power of 2
 * 2.  n = list_size should be evenly divisible by thread_count
 *
 * Additions made by: Nick Burnam
 * 1. Array Size allocation to fit nearest power of 2
 * 2. Dummy Record padding to fill array
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <vector>
#include <string>
#include "Bitonic_Sort_Serial.h"
#include "file_reader.h"

/* Random values in the range 0 to RMAX-1 */
//#define RMAX 1000000
#define RMAX 100

int thread_count = 4;
//pthread_barrier_t barrier;
int bar_count = 0;
pthread_mutex_t bar_mutex;
pthread_cond_t bar_cond;
int size;
int n;
std::vector<Record> *llc_file_vector;
int *list1, *list2;
int *l_a, *l_b;

int getNextPowerOf2(int size);
//void paddArray(std::vector<Record> *recordVector, int originalSize, int newSize);
void paddArray(int originalSize, int newSize);
void Usage(char *prog_name);
void Get_args(int argc, char *argv[]);
//void Gen_list(int list[], int size, int newSize);
//void Read_list(char prompt[], int list[], int n);
void Print_list();
void* Bitonic_sort(void *rank);
void Bitonic_sort_incr(int th_count, int dim, int my_first, int local_n,
		int my_rank);
void Bitonic_sort_decr(int th_count, int dim, int my_first, int local_n,
		int my_rank);
void Merge_split_lo(int my_rank, int my_first, int local_n, int partner);
void Merge_split_hi(int my_rank, int my_first, int local_n, int partner);
void Barrier(void);

/*--------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	long thread;
	pthread_t *thread_handles;
	struct timeval start, end;
	//int gen_list, output_list;

	//Need to create tempvector because return from fileToVector goes out of scope
	std::vector<Record> tempVector = fileToVector("llc_fnll_202003");
	llc_file_vector = &tempVector;

	printf("Done reading file...\n");
	//Get_args(argc, argv, &gen_list, &output_list);

	int vecLength = llc_file_vector->size();

	n = getNextPowerOf2(vecLength);

	printf("Input size: %d\n", vecLength);
	printf("Size with dummy records (after paddArray): %d\n", n);
	printf("Number of threads: %d\n", thread_count);

	thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
	pthread_mutex_init(&bar_mutex, NULL);
	pthread_cond_init(&bar_cond, NULL);
	/*
	list1 = (int*)malloc(n * sizeof(int));
	list2 = (int*)malloc(n * sizeof(int));
	l_a = list1;
	l_b = list2;

	if (gen_list)
		Gen_list(list1, size, n);
	else
		Read_list("Enter the list", list1, n);
	if (output_list)
		Print_list("The input list is", list1, n);
	*/
	// start timer
	//
	gettimeofday(&start, NULL);

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Bitonic_sort,
				(void*) thread);
	printf("BEFORE PTHREAD_JOIN ------\n");
	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	printf("AFTER PTHREAD_JOIHN ------\n");

	// get time
	//
	gettimeofday(&end, NULL);
	printf("Elapsed time = %f seconds\n",
			(double) (end.tv_sec - start.tv_sec)
					+ (double) (end.tv_usec - start.tv_usec) / 1000000);
/*
	if (output_list)
		Print_list("The sorted list is", l_a, n);

	free(list1);
	free(list2);
*/
	pthread_mutex_destroy(&bar_mutex);
	pthread_cond_destroy(&bar_cond);
	free(thread_handles);
	printf("before print list");
	Print_list();
	return 0;
} /* main */

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

void paddArray(int originalSize, int newSize) {
	srand(time(NULL));
	Record r;
	/*for (int i = 0; i < originalSize; i++) {
		// Fill with random integers
		//
		recordVector->at(i) = rand() % RMAX;
	}*/

	for (int i = originalSize; i < newSize; i++) {
		// Pad with dummy records
		//
		r = r.makeDummyRecord();
		llc_file_vector->push_back(r);
	}
}

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char *prog_name) {

	fprintf(stderr, "usage: %s <thread count> <n> [g] [o]\n", prog_name);
	fprintf(stderr, "n = number of elements in list\n");
	fprintf(stderr, "n should be evenly divisible by thread count\n");
	fprintf(stderr, "'g':  program should generate the list\n");
	fprintf(stderr, "'o':  program should output original and sorted lists\n");
	exit(0);
} /* Usage */

/*-------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get command line args
 * In args:     argc, argv
 * Out args:    gen_list_p, output_list_p
 * Out global:  n
 */
void Get_args(int argc, char *argv[]) {
	char c1;

	if (argc < 3 || argc > 5)
		Usage(argv[0]);
	thread_count = strtol(argv[1], NULL, 10);
	size = strtol(argv[2], NULL, 10);
	if (n % thread_count != 0)
		Usage(argv[0]);

	// if (argc == 3)
	/*
	*gen_list_p = *output_list_p = 0;

	if (argc == 4) {
		c1 = argv[3][0];
		if (c1 == 'g')
			*gen_list_p = 1;
		else
			*output_list_p = 1;
	} else if (argc == 5) {
		*gen_list_p = 1;
		*output_list_p = 1;
	}*/
} /* Get_args */

/*-------------------------------------------------------------------
 * Function:  Gen_list
 * Purpose:   Use a random number generator to generate a list of ints
 * In arg:    n
 * Out arg:   list
 * In global: RMAX
 */
/*
void Gen_list(int list[], int size, int newSize) {
	paddArray(list, size, newSize);
} /* Gen_list */

/*-------------------------------------------------------------------
 * Function:  Read_list
 * Purpose:   Get a list of ints from stdin
 * In arg:    n
 * Out arg:   list
 *//*
void Read_list(char prompt[], int list[], int n) {
	int i;

	printf("%s\n", prompt);
	for (i = 0; i < n; i++)
		scanf("%d", &list[i]);
} /* Read_list */

/*-------------------------------------------------------------------
 * Function:  Print_list
 * Purpose:   Print a list of ints to stdout
 * In args:   list, n
 */
void Print_list() {
	for (int i = 0; i < 50; i++) {
		std:: cout << llc_file_vector->at(i) << '\n';
	}
} /* Print_list */

/*-------------------------------------------------------------------
 * Function:        Bitonic_sort
 * Purpose:         Implement bitonic sort of a list of ints
 * In arg:          rank
 * In globals:      barrier, thread_count, n (list size), list1
 * Out global:      l_a
 * Scratch globals: list2, l_b
 * Return val:      Ignored
 */
void* Bitonic_sort(void *rank) {
	long tmp = (long) rank;
	int my_rank = (int) tmp;
	int local_n = n / thread_count;
	int my_first = my_rank * local_n;
	unsigned th_count, and_bit, dim;
	//printf("My Rank %d | Local N %d | My First %d\n", my_rank, local_n, my_first);

	/* Sort my sublist */
	//qsort(list1 + my_first, local_n, sizeof(int), Compare);

	bitonic_sort_seq(llc_file_vector + my_first, local_n, 1);

	Barrier();
#  ifdef DEBUG
   //if (my_rank == 0) Print_list("List after sort", list1, n);
#  endif
	for (th_count = 2, and_bit = 2, dim = 1; th_count <= thread_count;
			th_count <<= 1, and_bit <<= 1, dim++) {
		if ((my_rank & and_bit) == 0)
			Bitonic_sort_incr(th_count, dim, my_first, local_n, my_rank);
		else
			Bitonic_sort_decr(th_count, dim, my_first, local_n, my_rank);
	}

	return NULL;
} /* Bitonic_sort */

/*-------------------------------------------------------------------
 * Function:      Bitonic_sort_incr
 * Purpose:       Use parallel bitonic sort to sort a list into
 *                   increasing order.  This implements a butterfly
 *                   communication scheme among the threads
 * In args:       th_count:  the number of threads participating
 *                   in this sort
 *                dim:  base 2 log of th_count
 *                my_first:  the subscript of my first element in l_a
 *                local_n:  the number of elements assigned to each
 *                   thread
 *                 my_rank:  the calling thread's global rank
 * In/out global:  l_a pointer to current list.
 * Scratch global: l_b pointer to temporary list.
 */
void Bitonic_sort_incr(int th_count, int dim, int my_first, int local_n,
		int my_rank) {
	int stage;
	int partner;
	int *tmp;
	unsigned eor_bit = 1 << (dim - 1);

	for (stage = 0; stage < dim; stage++) {
		partner = my_rank ^ eor_bit;
		if (my_rank < partner)
			Merge_split_lo(my_rank, my_first, local_n, partner);
		else
			Merge_split_hi(my_rank, my_first, local_n, partner);
		eor_bit >>= 1;
		Barrier();
		if (my_rank == 0) {
#        ifdef DEBUG
         char title[1000];
#        endif
			tmp = l_a;
			l_a = l_b;
			l_b = tmp;
#        ifdef DEBUG
         sprintf(title, "Th_count = %d, stage = %d", th_count, stage);
         Print_list(title, l_a, n);
#        endif
		}
		Barrier();
	}

} /* Bitonic_sort_incr */

/*-------------------------------------------------------------------
 * Function:      Bitonic_sort_decr
 * Purpose:       Use parallel bitonic sort to sort a list into
 *                   decreasing order.  This implements a butterfly
 *                   communication scheme among the threads
 * In args:       th_count:  the number of threads participating
 *                   in this sort
 *                dim:  base 2 log of th_count
 *                my_first:  the subscript of my first element in l_a
 *                local_n:  the number of elements assigned to each
 *                   thread
 *                 my_rank:  the calling thread's global rank
 * In/out global:  l_a pointer to current list.
 * Scratch global: l_b pointer to temporary list.
 */
void Bitonic_sort_decr(int th_count, int dim, int my_first, int local_n,
		int my_rank) {
	int stage;
	int partner;
	int *tmp;
	unsigned eor_bit = 1 << (dim - 1);

	for (stage = 0; stage < dim; stage++) {
		partner = my_rank ^ eor_bit;
		if (my_rank > partner)
			Merge_split_lo(my_rank, my_first, local_n, partner);
		else
			Merge_split_hi(my_rank, my_first, local_n, partner);
		eor_bit >>= 1;
		Barrier();
		if (my_rank == 0) {
#        ifdef DEBUG
         char title[1000];
#        endif
			tmp = l_a;
			l_a = l_b;
			l_b = tmp;
#        ifdef DEBUG
         sprintf(title, "Th_count = %d, stage = %d", th_count, stage);
         Print_list(title, l_a, n);
#        endif
		}
		Barrier();
	}

} /* Bitonic_sort_decr */

/*-------------------------------------------------------------------
 * Function:        Merge_split_lo
 * Purpose:         Merge two sublists in array l_a keeping lower half
 *                  in l_b
 * In args:         partner, local_n
 * In/out global:   l_a
 * Scratch:         l_b
 */
void Merge_split_lo(int my_rank, int my_first, int local_n, int partner) {
	int ai, bi, xi, i;

	ai = bi = my_first;
	xi = partner * local_n;

#  ifdef DDEBUG
   printf("Th %d > In M_s_lo partner = %d, ai = %d, xi = %d\n",
         my_rank, partner, ai, xi);
#  endif
	for (i = 0; i < local_n; i++)
		if (l_a[ai] <= l_a[xi]) {
			l_b[bi++] = l_a[ai++];
		} else {
			l_b[bi++] = l_a[xi++];
		}

} /* Merge_split_lo */

/*-------------------------------------------------------------------
 * Function:        Merge_split_hi
 * Purpose:         Merge two sublists in array l_a keeping upper half
 *                  in l_b
 * In args:         partner, local_n
 * In/out global:   l_a
 * Scratch:         l_b
 */
void Merge_split_hi(int my_rank, int my_first, int local_n, int partner) {
	int ai, bi, xi, i;

	ai = bi = my_first + local_n - 1;
	xi = (partner + 1) * local_n - 1;

#  ifdef DDEBUG
   printf("Th %d > In M_s_hi partner = %d, ai = %d, xi = %d\n",
         my_rank, partner, ai, xi);
#  endif

	for (i = 0; i < local_n; i++)
		if (l_a[ai] >= l_a[xi])
			l_b[bi--] = l_a[ai--];
		else
			l_b[bi--] = l_a[xi--];

} /* Merge_split_hi */

/*-------------------------------------------------------------------
 * Function:  Barrier
 * Purpose:   Block all threads until all threads have called
 *            Barrier
 * Globals:   bar_count, bar_mutex, bar_cond
 */
void Barrier(void) {
	pthread_mutex_lock(&bar_mutex);
	bar_count++;
	if (bar_count == thread_count) {
		bar_count = 0;
		pthread_cond_broadcast(&bar_cond);
	} else {
		while (pthread_cond_wait(&bar_cond, &bar_mutex) != 0)
			;
	}
	pthread_mutex_unlock(&bar_mutex);
} /* Barrier */
