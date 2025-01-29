#include "StringPropertie.h"

StringPropertie::StringPropertie(std::string title, std::string value)
	: Propertie(title, value, "string")
{
}

std::string StringPropertie::getStrValue()
{
	return value;
}
