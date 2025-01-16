#pragma once
#include "TinyXml.h"

#include "../functions.h"

class TinyClass
{
	int id;
	char* name;

	std::vector<std::shared_ptr<ICollision>> objects;
public:
	TinyClass(int id, const char* name, std::vector<std::shared_ptr<ICollision>> objects);
	TinyClass(tinyxml2::XMLElement* element);

	static void GetObjects(tinyxml2::XMLElement* element, std::vector<std::shared_ptr<ICollision>>& objects);

	std::vector<std::shared_ptr<ICollision>>::iterator begin();
	std::vector<std::shared_ptr<ICollision>>::iterator end();

	int GetId();
	char* GetName();
	int GetSize();

	std::weak_ptr<ICollision> operator[](int index);
};