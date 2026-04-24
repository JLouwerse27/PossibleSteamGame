#pragma once
#include <string>

class JFileManager {
private:
	std::string fileName;
public:
	JFileManager(std::string);
	void readFile();
};