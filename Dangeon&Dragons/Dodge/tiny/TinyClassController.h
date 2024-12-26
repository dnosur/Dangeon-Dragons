#pragma once
#include "TinyClass.h"

#include <boost/container/vector.hpp>

class TinyClassController
{
	boost::container::vector<TinyClass> classes;
public:
	TinyClassController();
	TinyClassController(boost::container::vector<TinyClass> classes);
	TinyClassController(tinyxml2::XMLElement* element);
	~TinyClassController();

	static void LoadClasses(tinyxml2::XMLElement* element, boost::container::vector<TinyClass>& classes);

	boost::container::vector<TinyClass>::iterator begin();
	boost::container::vector<TinyClass>::iterator end();

	int GetSize();
	
	TinyClass* GetById(int id);

	TinyClass* operator[](const char* name);
	TinyClass* operator[](int index);
};

