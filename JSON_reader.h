#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class JSON_reader {
	string main_path;
	ifstream in;

	string minimum_path; //Костыль(?)

	//Строковое представление комманд для удобства:
	const string dataset_folder = "dataset_folder";
	const string include_folders = "include_folders";
	const string include_files = "include_files";
	const string folder_name = "folder_name";

	string string_formation(const string&, const string&);
	void create_files(const string&);

public:
	JSON_reader(const string& fileName);

	~JSON_reader();

	void read();
};