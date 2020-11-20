#include "file_reader.h"


using namespace std;


// read file into an array for future manip/sorting
vector<Record> fileToVector(string fileName) {
	cout << "In file reader\n";
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "unable to open file\n";
        exit(1);
    }
    //return vector of record objects that represent each line
    vector<Record> records;
    Record r;
    string line;

    while (getline(inputFile, line))
    {
    	istringstream ss(line);
    	ss >> r;

    	records.push_back(r);
    }

    cout << "outputVector size is: " << records.size() << endl;
    //this entry is used as an example because it has a blank field, handles error cases.
    cout << "Entry : " << records.at(189654)<< endl;

    return records;
}
