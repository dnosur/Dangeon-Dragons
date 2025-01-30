#include "TinyClassController.h"

TinyClassController::TinyClassController()
{
}

TinyClassController::TinyClassController(std::unordered_map<int, std::shared_ptr<TinyClass>> classes)
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

void TinyClassController::LoadClasses(tinyxml2::XMLElement* element, std::unordered_map<int, std::shared_ptr<TinyClass>>& classes)
{
	for (tinyxml2::XMLElement* child = element->FirstChildElement("group");
		child != nullptr;
		child = child->NextSiblingElement("group")
	)
	{
		std::unique_ptr<TinyClass> temp = std::make_unique<TinyClass>(child);
		classes[temp->GetId()] = std::move(temp);
	}
}

std::unordered_map<int, std::shared_ptr<TinyClass>>::iterator TinyClassController::begin()
{
	return classes.begin();
}

std::unordered_map<int, std::shared_ptr<TinyClass>>::iterator TinyClassController::end()
{
	return classes.end();
}

int TinyClassController::GetSize()
{
	return classes.size();
}

std::weak_ptr<TinyClass> TinyClassController::GetById(int id)
{
	auto it = classes.find(id);
	if (it == classes.end()) {
		return {};
	}
	return it->second;
}

std::weak_ptr<TinyClass> TinyClassController::operator[](std::string_view name)
{
	for (auto& it : classes) {
		if (it.second->GetName() == name) {
			return it.second;
		}
	}
	return {};
}

std::weak_ptr<TinyClass>TinyClassController::operator[](int index)
{
	if (index < 0 || index >= classes.size())
	{
		return {};
	}

	auto it = classes.begin();
	std::advance(it, index);
	return it->second;
}
