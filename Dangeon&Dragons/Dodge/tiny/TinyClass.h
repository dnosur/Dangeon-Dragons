#pragma once
#include "TinyXml.h"

#include "../functions.h"

class TinyClass
{
	int id;
	std::string name;

	std::vector<std::shared_ptr<ICollision>> objects;
public:
	TinyClass(int id, std::string name, std::vector<std::shared_ptr<ICollision>> objects);
	TinyClass(tinyxml2::XMLElement* element);

	static void GetObjects(tinyxml2::XMLElement* element, std::vector<std::shared_ptr<ICollision>>& objects);

	std::vector<std::shared_ptr<ICollision>>::iterator begin();
	std::vector<std::shared_ptr<ICollision>>::iterator end();

	int GetId();
	std::string_view GetName();
	int GetSize();

	std::weak_ptr<ICollision> operator[](int index);
};