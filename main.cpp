#include "JSON_reader.h"
//C++ 17+
int main(int argc, char *argv[]) {
	if (argc > 1) {
		for (size_t i = 1; i < argc; ++i) {
			JSON_reader reader(argv[i]);
			reader.read();
		}
	}
	else {
		cout << "Select Path to Json:" << endl;
		string line;
		getline(cin, line);
		JSON_reader reader(line);
		reader.read();
	}

	/*
	JSON_reader reader("json.txt");
	reader.read();
	*/

	return 0;
}