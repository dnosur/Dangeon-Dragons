#include "Propertie.h"
#include "../../functions.h"

Propertie::Propertie()
{
	title = value = type = nullptr;
}

Propertie::Propertie(char* title, char* value, char* type)
{
	copyStr(this->title, title);
	copyStr(this->value, value);
	copyStr(this->type, type);
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
