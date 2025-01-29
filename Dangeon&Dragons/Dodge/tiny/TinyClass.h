#pragma once
#include "TinyXml.h"

#include "../functions.h"

class TinyClass
{
	int id;
	std::string name;

	std::vector<ICollision*> objects;
public:
<<<<<<< Updated upstream
	TinyClass(int id, const char* name, std::vector<ICollision*> objects);
=======
	TinyClass(int id, std::string name, std::vector<std::shared_ptr<ICollision>> objects);
>>>>>>> Stashed changes
	TinyClass(tinyxml2::XMLElement* element);
	~TinyClass();

	static void GetObjects(tinyxml2::XMLElement* element, std::vector<ICollision*>& objects);

	std::vector<ICollision*>::iterator begin();
	std::vector<ICollision*>::iterator end();

	int GetId();
	std::string GetName();
	int GetSize();

	ICollision* operator[](int index);
};