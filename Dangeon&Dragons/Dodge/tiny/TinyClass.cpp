#include "TinyClass.h"

TinyClass::TinyClass(int id, std::string name, std::vector<std::shared_ptr<ICollision>> objects)
{
	this->id = id;
	this->name = name;
	this->objects = objects;
}

TinyClass::TinyClass(tinyxml2::XMLElement* element)
{
	id = element->IntAttribute("id");
	std::string name = element->Attribute("name");
	this->name = name;

	GetObjects(element, objects);
}

void TinyClass::GetObjects(tinyxml2::XMLElement* element, std::vector<std::shared_ptr<ICollision>>& objects)
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
					std::make_shared<BoxCollision>(
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
				std::make_shared<PoligonCollision>(
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

std::vector<std::shared_ptr<ICollision>>::iterator TinyClass::begin()
{
	return objects.begin();
}

std::vector<std::shared_ptr<ICollision>>::iterator TinyClass::end()
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

std::weak_ptr<ICollision> TinyClass::operator[](int index)
{
	if (index < 0 || index >= objects.size())
	{
		return std::make_shared<BoxCollision>();
	}
	return objects[index];
}
