#include "TinyClassController.h"

TinyClassController::TinyClassController()
{
	classes = std::vector<TinyClass>();
}

TinyClassController::TinyClassController(std::vector<TinyClass> classes)
{
	this->classes = classes;
}

TinyClassController::TinyClassController(tinyxml2::XMLElement* element)
{
	LoadClasses(element, classes);
}

TinyClassController::~TinyClassController()
{
}

void TinyClassController::LoadClasses(tinyxml2::XMLElement* element, std::vector<TinyClass>& classes)
{
	for (tinyxml2::XMLElement* child = element->FirstChildElement("group");
		child != nullptr;
		child = child->NextSiblingElement("group")
	)
	{
		classes.push_back(TinyClass(child));
	}
}

std::vector<TinyClass>::iterator TinyClassController::begin()
{
	return classes.begin();
}

std::vector<TinyClass>::iterator TinyClassController::end()
{
	return classes.end();
}

int TinyClassController::GetSize()
{
	return classes.size();
}

TinyClass* TinyClassController::GetById(int id)
{
	for (int i = 0; i < classes.size(); i++)
	{
		if (classes[i].GetId() == id)
		{
			return &classes[i];
		}
	}
	return nullptr;
}

TinyClass* TinyClassController::operator[](const char* name)
{
	for (int i = 0; i < classes.size(); i++)
	{
		if (strcmp(classes[i].GetName(), name) == 0)
		{
			return &classes[i];
		}
	}
	return nullptr;
}

TinyClass* TinyClassController::operator[](int index)
{
	if (index < 0 || index >= classes.size())
	{
		return nullptr;
	}
	return &classes[index];
}
