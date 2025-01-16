#pragma once
#include "TinyXml.h"

#include "../functions.h"

class TinyClass
{
	int id;
	char* name;

	std::vector<ICollision*> objects;
public:
	TinyClass(int id, const char* name, std::vector<ICollision*> objects);
	TinyClass(tinyxml2::XMLElement* element);
	~TinyClass();

	static void GetObjects(tinyxml2::XMLElement* element, std::vector<ICollision*>& objects);

	std::vector<ICollision*>::iterator begin();
	std::vector<ICollision*>::iterator end();

	int GetId();
	char* GetName();
	int GetSize();

	ICollision* operator[](int index);
};