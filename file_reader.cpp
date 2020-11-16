#include "file_reader.h"


using namespace std;



// read file into an array for future manip/sorting
vector<Record> fileToVector(string fileName) {
	cout << "In file reader\n";
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "unable to open file";
        exit(1);
    }
    //return vector containing strings representing each line of llc_fnl file
    vector<Record> records;
    
    /*I removed this because due to large RAM it's not really needed, can change implementation if issue
    constexpr size_t bufferSize = 1024 * 1024;
    unique_ptr<char[]> buffer(new char[bufferSize]);
     *
     */
    Record r;
    while (inputFile >> r)
    {
        //try to take each line and push it into the vector for
        //easier manipulation in the future

    	records.push_back(r);
    }

    cout << "outputVector size is: " << records.size() << endl;
    cout << "First entry is: " << records.at(0)<< endl;
/*
    for (int i = 0; i < 25; i++) {
    	cout  >> outputVector.at(i);
    }*/

    return records;
}
