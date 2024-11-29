#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Save
{
public:
	static void SaveData(const char* path, std::vector<std::pair<std::string, std::string>> data, bool rewrite = false);
	static std::vector<std::pair<std::string, std::string>> LoadData(const char* path);
};