// This program is used to copy one file to another within the same directory written by Lucian Dupont-Leblanc
//
//invocation is  ./myCopier <file to be copied> <file to copy to>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc , char* argv[]){

	std::string file1name = argv[1];
	std::string file2name = argv[2];

	std::ifstream inputFile(file1name);

	std::ofstream outputFile(file2name);

	if (inputFile.is_open() && outputFile.is_open())
	{
		std::string line;
	while (std::getline(inputFile, line))
	{
	outputFile << line << "\n";
	}

	inputFile.close();
	outputFile.close();

	std::cout << "File Done Copying" << endl;
	}
	else 
	{
	cout << "File Failed to Copy" << endl;
	}
	return 0;
}
