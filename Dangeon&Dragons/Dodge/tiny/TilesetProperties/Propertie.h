#pragma once

class Propertie
{
protected:
	char* title;
	char* value;
	char* type;
public:
	Propertie();
	Propertie(char* title, char* value, const char* type);
	~Propertie();

	char* getTitle();
	char* getValue();
	char* getType();

	bool operator==(const Propertie& other) const;
	bool operator!=(const Propertie& other) const;
	Propertie& operator=(const Propertie& other);
};