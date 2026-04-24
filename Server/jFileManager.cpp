#include "jFileManager.h"
#include <iostream>
#include <fstream>

JFileManager::JFileManager(std::string fn) : fileName(fn) {};

void JFileManager::readFile() {
	std::ifstream ist{ fileName }; // ist is an input stream for the file named name
	if (!ist)
		std::cout << "can't open input file " << fileName;
};