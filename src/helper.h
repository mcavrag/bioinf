#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Helper {

	static int readInputFa(string inputFilePath, string& S);

    static int readInputK(string inputFilePath, uint64_t& k);

    //static int printToFile() - TODO
};

#endif //HELPER_H