#include "helper.h"

int Helper::readInputFa(string inputFilePath, string& S)
{
	ifstream inputFile(inputFilePath);

	if (!inputFile.is_open())
	{
		cout << "Unable to open file" << endl; 
		return 1;	
	} 

	int stringNum = 0;

	string line;

	while ( getline (inputFile,line) )
	{
		if(line[0] == '>')
		{
			if(stringNum)
			{
				// This is added to seperate sequences
				S.resize(S.size() + 1);
				S[S.size() - 1] = '%';
			}
			stringNum++;
			continue;
		}
		S += line;
	}
	
	return 0;
}

int Helper::readInputK(string inputFilePath, uint64_t& k)
{
	ifstream inputFile(inputFilePath);

	if (!inputFile.is_open())
	{
		cerr << "Unable to open file" << endl; 
		return 1;	
	} 

	string line;

	if(!getline (inputFile,line))
	{
		cerr << "Empty file!" << endl;
		return 1;
	}

	k = stoi(line);

	inputFile.close();

	return 0;
}