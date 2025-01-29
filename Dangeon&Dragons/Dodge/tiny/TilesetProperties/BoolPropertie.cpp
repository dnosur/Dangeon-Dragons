#include "BoolPropertie.h"
#include <string.h>

BoolPropertie::BoolPropertie(std::string title, std::string value)
	: Propertie(title, value, "bool")
{
	boolValue = value == "true";
}

bool BoolPropertie::getBoolValue()
{
	return boolValue;
}
