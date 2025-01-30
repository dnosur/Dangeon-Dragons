#pragma once
#include "TinyClass.h"

#include <unordered_map>

class TinyClassController
{
	std::unordered_map<int, std::shared_ptr<TinyClass>> classes;
public:
	TinyClassController();
	TinyClassController(std::unordered_map<int, std::shared_ptr<TinyClass>> classes);
	TinyClassController(tinyxml2::XMLElement* element);
	~TinyClassController();

	static void LoadClasses(tinyxml2::XMLElement* element, std::unordered_map<int, std::shared_ptr<TinyClass>>& classes);

	std::unordered_map<int, std::shared_ptr<TinyClass>>::iterator begin();
	std::unordered_map<int, std::shared_ptr<TinyClass>>::iterator end();

	int GetSize();
	
	std::weak_ptr<TinyClass> GetById(int id);

	std::weak_ptr<TinyClass>operator[](std::string_view name);
	std::weak_ptr<TinyClass> operator[](int index);
};

