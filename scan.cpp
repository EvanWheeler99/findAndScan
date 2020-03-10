// CPSC 457 Assignment 2 Q3
//Usage: ./scan [suffix] [N] [type]

// By: Evan Wheeler
// UCID# 30046173


#include<sys/types.h>
#include<sys/stat.h>
#include<string>
#include<cstring>
#include<sys/wait.h>
#include<signal.h>
#include<iostream>
#include<vector>
#include<bits/stdc++.h>


using namespace std;


//A struct that will store the names of files along with their sizes
struct File_type {
	string fileName;
	double fileSize;
};


//Function to print a vector, (for debugging)
void printVector(vector<string> const &input) {
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i);
	}
}


//Checks if toMatch is a suffix of mainStr
bool isSuffix(const string &mainStr, const string &toMatch) {
	if(mainStr.size() >= toMatch.size() && mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
		return true;
	else
		return false;
}


//Uses stat() to return the size of a file as a double
double getFilesize(const string& filename) {
	struct stat st;
	if(stat(filename.c_str(), &st) != 0) {
		return 0;
	}
	return static_cast<double>(st.st_size);
}


//Comparator for increasing files
bool compareFileSizesIncreasing(File_type f1, File_type f2) {
	return (f1.fileSize > f2.fileSize);
}


//Comparator for decreasing files
bool compareFileSizesDecreasing(File_type f1, File_type f2) {
	return (f1.fileSize < f2.fileSize);
}


//Main routine
int main(int argc, char* argv[]){

	// Check args
	if (argc != 4) {
		cout << "Usage: ./scan [suffix] [N] [type]" << endl;
		exit(1);
	}

	// Get params
	char *suff = argv[1];
	string suffix(suff);	//Cast suffix to string

	int n = atoi(argv[2]);
	int type = atoi(argv[3]);


	//Constant global values
	// register int MAX_NUM_FILES = 999;	//Unused
	register int MAX_NAME = 512;

	FILE *fd;
	fd = popen("./myFind", "r");
	if(!fd){
		cout<< "Cannot be piped"<< endl;
	}

	vector<string> fileNameVector;
	char buff[ MAX_NAME ];
	int numFiles = 0;

	// Iterate through file names
	while(fgets(buff, MAX_NAME, fd)) {

		//Cast buffer to string
		string name(buff);
		//Remove newline char from the name
		name.pop_back();

		//Check if the file ends with the suffix
		if (isSuffix(name, suffix)){
			//Add filename to the vector
			fileNameVector.push_back(name);
			numFiles++;
		}
	}
	//Close fd
	pclose(fd);

	//Init var to store the size of ALL files with the suffix
	long long totalFileSize = 0;

	//Create File_type array
	File_type* validFiles = new File_type[numFiles];

	//var to temporarily hold the file size
	register double sizeOfFile;

	//Fill the array
	for( int i = 0; i < numFiles; i++) {
		validFiles[i].fileName = fileNameVector[i];
		sizeOfFile = getFilesize(fileNameVector[i]);
		validFiles[i].fileSize = sizeOfFile;
		totalFileSize += sizeOfFile;
	}

	//Sort the files based on the [type]
	// int temp = sizeof(validFiles)/sizeof(validFiles[0]);
	if (type == 0) {;
		sort(validFiles, validFiles + numFiles, compareFileSizesDecreasing);
	} else {
		sort(validFiles, validFiles + numFiles, compareFileSizesIncreasing);
	}

	//Set n = numFiles so that we will not try and Iterate
	//Over more files than there exist
	if (n > numFiles) {
		n = numFiles;
	}

	long long nFileSize = 0;		//The size of N files
	for (int i = 0; i < n; i++) {
		sizeOfFile = validFiles[i].fileSize;
		//Print out N files and their sizes
		cout << validFiles[i].fileName << "\t" << sizeOfFile << endl;
		nFileSize += sizeOfFile;
	}

	// Print out the total file size
	cout << "Total Size:\t" << totalFileSize << endl;

	// Print the size of N files
	cout << "Part size:\t" << nFileSize << endl;

	//Calculate the percentage
	int percent = (100 * nFileSize) / totalFileSize;

	//Print the percentage
	cout << "Percent:\t" << percent << endl;

	return 0;
}
