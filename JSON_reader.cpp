#include "JSON_reader.h"
#include <filesystem>
#include <iostream>
//Конструктор:
JSON_reader::JSON_reader(const string& fileName){
	in.open(fileName);
	if (in.is_open()) {
		string line;
		while (line.find(dataset_folder) == string::npos) {
			getline(in, line);	
		}

		main_path = string_formation(line, dataset_folder);
		filesystem::create_directory(main_path);
		minimum_path = main_path;
	}
	else {
		cout << "ERROR! File is not Open!" << endl;
	}
}

//Деструктор:
JSON_reader::~JSON_reader() {
	in.close();
}

//Формирование нужной строки:
string JSON_reader::string_formation(const string& line, const string& str) {
		int index = line.find(str) + str.length() + 1;
		while (line[index] != '"') {
			++index;
		}
		++index;
		string res;
		while (line[index] != '"') {
			res += line[index];
			++index;
		}
		return res;	
}

//Создание файлов:
void JSON_reader::create_files(const string& thread) {
	ofstream file;
	int index = thread.find(include_files) + include_files.length() + 1;
	while (thread[index] != '[') {
		index++;
	}
	bool flag = true;
	while (thread[index] != ']') {
		if (thread[index] == '"' && flag) {
			++index;
			string tmp = "/";
			while (thread[index] != '"') {
				tmp += thread[index];
				index++;
			}
			file.open(main_path + tmp + ".txt");
			file.close();
			flag = false;
		}
		else {
			index++;
			flag = true;
		}
	}
}

//Считывание и анализ данных из файла JSON:
void JSON_reader::read() {
	string line;
	while (getline(in, line)) {
		if (line.find(include_folders) != string::npos) {
		}
		else if (line.find(include_files) != string::npos) {
			create_files(line);
		}
		else if (line.find(folder_name) != string::npos) {
			main_path += '/';
			main_path += string_formation(line, folder_name);
			if ((filesystem::exists(main_path) && filesystem::is_directory(main_path))) {
				try {
					filesystem::remove_all(main_path);
				}
				catch (filesystem::filesystem_error& err) {
					cout << "Error! Close files and try again!" << endl;
					break;
				}
			}
			filesystem::create_directory(main_path);
			try {
				filesystem::create_directory(main_path);
			}
			catch (filesystem::filesystem_error& err) {

				cout << "Error! Close files and try again!" << endl;

				break;
			}
		}
		else {
			if ((line.find('}') != string::npos) || (line.find(']') != string::npos)) {
				while ((main_path[main_path.size() - 1] != '/') && (main_path.find('/') != string::npos)) {
					main_path.pop_back();
				}
				if (main_path.size() > minimum_path.size()) {
					main_path.pop_back();
				}
			}
		}
	}
}