# PBNS_KDS

Up-to-date PBNS record implementation. Can properly read input from llc file, just need to implement sorting based on desired column.

# Pthread version Compilation with g++
g++ -O3 Bitonic_Sort_Main.cpp -lpthread Bitonic_Sort_Serial.cpp file_reader.cpp -o Bitonic-Sort

# OpenMP version Compilation with g++
g++ -O3 bitonicSort.cpp -fopenmp Bitonic_Sort_Serial.cpp file_reader.cpp -o Bitonic-Sort
