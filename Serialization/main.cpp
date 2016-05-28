#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#include "Tokenizer.h"

using namespace Parsing;




string readFile(const string& filename)
{
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();

	return buffer.str();
}

int main(int argc, char** argv)
{
	cout << "Serializer driver" << endl;

	vector<string> args;

	if (argc > 0)
	{
		cout << "Processing command line arguments..." << endl;

		args.reserve(argc);

		for (int i = 0; i < argc; ++i)
		{
			string arg = string(argv[i]);

			args.push_back(arg);

			cout << "(" << i << ") \"" << arg << "\"" << endl;
		}
	}

	if (argc > 1)
	{
		string filename = args[1];
		cout << "Loading file \"" << filename << "\"" << endl;

		Tokenizer parser;

		string source = readFile(args[1]);

		cout << "Parsing..." << endl;

		parser.Reset(source);

		while (!parser.IsEOF())
		{
			auto t = parser.GetNextToken();

			cout << "Token: (" << (string)t << ")" << endl;
		}

		cout << "Done." << endl;
	}



	cout << "Press enter to exit." << endl;
	getchar();
}