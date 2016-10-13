/**
* This tool is used to automatically clean up camera folder
* Usage:
*	copy the program into a cam folder
*	select awesome jpeg files into selected folder
*	put all raw files into the raw folder
*   execute the program to kill the large raw files which are uncessary
*
* Ruofei Du
* Free software, yeah!
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <set>
#include <random>
#include <cstdio>
#include <cmath>
#include "windows.h"
#include "dirent.h"
using namespace std;

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

int main() {
	string exe_path = ExePath();
	cout << "Current directory is " << exe_path << "\n";

	DIR *dir;
	struct dirent *ent;
	string selected_path = exe_path + "\\selected";

	set<string> selected_set;
	if ((dir = opendir(selected_path.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string file = string(ent->d_name);
			string prefix = file.substr(0, file.find("."));
			selected_set.insert(prefix);
			printf("%s\n", prefix);

		}
		closedir(dir);
	}
	else {
		perror("");
		return EXIT_FAILURE;
	}

	cout << "\nRemoving...\n";
	string raw_path = exe_path + "\\raw";
	if ((dir = opendir(raw_path.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string file = string(ent->d_name);
			string prefix = file.substr(0, file.find("."));
			if (selected_set.find(prefix) == selected_set.end()) {
				file = exe_path + "\\raw\\" + file;
				cout << "Erase: " << file << endl;
				remove(file.c_str());
			}
		}
		closedir(dir);
	}
	else {
		perror("");
		return EXIT_FAILURE;
	}

	
	system("pause");
	return 0;
}
