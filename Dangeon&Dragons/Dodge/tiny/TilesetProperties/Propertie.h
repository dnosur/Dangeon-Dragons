#pragma once
#include <string>

class Propertie
{
protected:
	std::string title;
	std::string value;
	std::string type;
public:
	Propertie();
	Propertie(std::string title, std::string value, std::string type);
	~Propertie();

	std::string getTitle();
	std::string getValue();
	std::string getType();

	bool operator==(const Propertie& other) const;
	bool operator!=(const Propertie& other) const;
	Propertie& operator=(const Propertie& other);
};