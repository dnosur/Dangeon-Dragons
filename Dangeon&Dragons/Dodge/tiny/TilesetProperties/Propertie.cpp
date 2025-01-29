#include "Propertie.h"
#include "../../functions.h"

Propertie::Propertie()
{
}

Propertie::Propertie(std::string title, std::string value, std::string type)
	: title(title), value(value), type(type)
{
<<<<<<< Updated upstream
	copyStr(title, this->title);
	copyStr(value, this->value);
	copyStr(type, this->type);
=======
>>>>>>> Stashed changes
}

std::string Propertie::getTitle()
{
	return title;
}

std::string Propertie::getValue()
{
	return value;
}

std::string Propertie::getType()
{
	return type;
}

bool Propertie::operator==(const Propertie& other) const
{
	return title == other.title || value == other.value || type == other.type;
}

bool Propertie::operator!=(const Propertie& other) const
{
	return !(*this == other);
}

Propertie& Propertie::operator=(const Propertie& other)
{
	if (this != &other) {
<<<<<<< Updated upstream
		copyStr(other.title, title);
		copyStr(other.value, value);
		copyStr(other.type, type);
=======
		this->title = other.title;
		this->value = other.value;
		this->type = other.type;
>>>>>>> Stashed changes
	}
	return *this;
}

Propertie::~Propertie()
{
}
