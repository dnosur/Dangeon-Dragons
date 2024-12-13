#include "Propertie.h"
#include "../../functions.h"

Propertie::Propertie()
{
	title = value = type = nullptr;
}

Propertie::Propertie(char* title, char* value,const char* type)
{
	copyStr(title, this->title);
	copyStr(value, this->value);
	copyStr(type, this->type);
}

char* Propertie::getTitle()
{
	return title;
}

char* Propertie::getValue()
{
	return value;
}

char* Propertie::getType()
{
	return type;
}

bool Propertie::operator==(const Propertie& other) const
{
	return !strcmp(title, other.title) || !strcmp(value, other.value) || !strcmp(type, other.type);
}

bool Propertie::operator!=(const Propertie& other) const
{
	return !(*this == other);
}

Propertie& Propertie::operator=(const Propertie& other)
{
	if (this != &other) {
		copyStr(other.title, title);
		copyStr(other.value, value);
		copyStr(other.type, type);
	}
	return *this;
}

Propertie::~Propertie()
{
	if (title != nullptr) {
		delete[] title;
	}

	if (value != nullptr) {
		delete[] value;
	}

	if (type != nullptr) {
		delete[] type;
	}
}
