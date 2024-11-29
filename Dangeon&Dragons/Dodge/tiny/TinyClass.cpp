#include "TinyClass.h"

TinyClass::TinyClass(int id, const char* name, std::vector<ICollision*> objects)
{
	this->id = id;
	copyStr(name, this->name);
	this->objects = objects;
}

TinyClass::TinyClass(tinyxml2::XMLElement* element)
{
	id = element->IntAttribute("id");
	const char* name = element->Attribute("name");
	copyStr(name, this->name);

	GetObjects(element, objects);
}

TinyClass::~TinyClass()
{
}

void TinyClass::GetObjects(tinyxml2::XMLElement* element, std::vector<ICollision*>& objects)
{
	tinyxml2::XMLElement* objectGroup = element->FirstChildElement("objectgroup");
	if (objectGroup == nullptr)
	{
		return;
	}

	for (tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");
		object != nullptr;
		object = object->NextSiblingElement("object"))
	{
		const Coord coord = Coord(object->DoubleAttribute("x"), object->DoubleAttribute("y"));
		const Size size = Size(object->DoubleAttribute("width"), object->DoubleAttribute("height"));

		const int object_id = object->IntAttribute("id");
		const char* object_name = object->Attribute("name");
		const char* object_type = object->Attribute("type");

		tinyxml2::XMLElement* polygon = object->FirstChildElement("polygon");
		if (polygon == nullptr)
		{
			objects.push_back(
				new BoxCollision(
					coord,
					size,
					object_id,
					(char*)object_name,
					(char*)object_type
				)
			);
			continue;
		}

		objects.push_back(
			new PoligonCollision(
				TinyXml::ParsePolygon(
					polygon->Attribute("points"),
					coord
				),
				object_id,
				(char*)object_name,
				(char*)object_type
			)
		);
	}
}

std::vector<ICollision*>::iterator TinyClass::begin()
{
	return objects.begin();
}

std::vector<ICollision*>::iterator TinyClass::end()
{
	return objects.end();
}

int TinyClass::GetId()
{
	return id;
}

char* TinyClass::GetName()
{
	return name;
}

int TinyClass::GetSize()
{
	return objects.size();
}

ICollision* TinyClass::operator[](int index)
{
	if (index < 0 || index >= objects.size())
	{
		return nullptr;
	}
	return objects[index];
}
