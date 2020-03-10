// CPSC 457 Assignment 2 Q2

// By: Evan Wheeler
// UCID# 30046173

//Code modified from TA's code that can be found @
// https://docs.google.com/document/d/1-VV6yJmaTYO6MwEAHFJKXHcpdGCaVI_1UxUlDBYxKB8/edit

#include<iostream>
#include<dirent.h>
#include<cstring>


using namespace std;

void traverse(string path){

	DIR *dir = opendir(path.c_str());
	struct dirent *info = NULL;
	if(dir == NULL){
		cout << "Directory can't be opened" + path << "\n";
	}
	else{
		while(info = readdir(dir)){
			if(info -> d_type == DT_DIR){
			if(strcmp(info -> d_name, ".") == 0 || strcmp(info -> d_name, "..") == 0){
					continue;
				}
				else{
					string dir_name = path + "/" + info -> d_name;
					traverse(dir_name);
				}
		}
			else{
				string file_path = path + "/";
				cout<<file_path<<info -> d_name<< "\n";
			}
		}
	}
}
int main(){
	cout << "." << endl;
	traverse(".");
	return 0;
}
