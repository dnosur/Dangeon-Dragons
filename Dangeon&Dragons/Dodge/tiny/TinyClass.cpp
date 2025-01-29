#include "TinyClass.h"

<<<<<<< Updated upstream
TinyClass::TinyClass(int id, const char* name, std::vector<ICollision*> objects)
{
	this->id = id;
	copyStr(name, this->name);
=======
TinyClass::TinyClass(int id, std::string name, std::vector<std::shared_ptr<ICollision>> objects)
{
	this->id = id;
	this->name = name;
>>>>>>> Stashed changes
	this->objects = objects;
}

TinyClass::TinyClass(tinyxml2::XMLElement* element)
{
	id = element->IntAttribute("id");
<<<<<<< Updated upstream
	const char* name = element->Attribute("name");
	copyStr(name, this->name);
=======
	std::string name = element->Attribute("name");
	this->name = name;
>>>>>>> Stashed changes

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

	for (tinyxml2::XMLElement* objectGroup = element->FirstChildElement("objectgroup");
		objectGroup != nullptr;
		objectGroup = objectGroup->NextSiblingElement("objectgroup")
		) {

		for (tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");
			object != nullptr;
			object = object->NextSiblingElement("object"))
		{
			const Coord coord = Coord(object->DoubleAttribute("x"), object->DoubleAttribute("y"));
			const Size size = Size(object->DoubleAttribute("width"), object->DoubleAttribute("height"));

			const int object_id = object->IntAttribute("id");
			std::string object_name = object->Attribute("name");
			std::string object_type = object->Attribute("type");

			tinyxml2::XMLElement* polygon = object->FirstChildElement("polygon");
			if (polygon == nullptr)
			{
				objects.push_back(
					new BoxCollision(
						coord,
						size,
						object_id,
						object_name,
						object_type
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
					object_name,
					object_type
				)
			);
		}
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

std::string TinyClass::GetName()
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
