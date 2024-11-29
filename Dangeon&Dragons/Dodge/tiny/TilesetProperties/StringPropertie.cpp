#include "StringPropertie.h"

StringPropertie::StringPropertie(char* name, char* value)
	: Propertie(name, value, (char*)"string")
{
}

std::string StringPropertie::getStrValue()
{
	return value;
}
