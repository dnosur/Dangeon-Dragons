#pragma once
#include "TinyClass.h"

class TinyClassController
{
	std::vector<TinyClass> classes;
public:
	TinyClassController();
	TinyClassController(std::vector<TinyClass> classes);
	TinyClassController(tinyxml2::XMLElement* element);
	~TinyClassController();

	static void LoadClasses(tinyxml2::XMLElement* element, std::vector<TinyClass>& classes);

	std::vector<TinyClass>::iterator begin();
	std::vector<TinyClass>::iterator end();

	int GetSize();
	
	TinyClass* GetById(int id);

	TinyClass* operator[](const char* name);
	TinyClass* operator[](int index);
};

