#include "IntPropertie.h"
#include <string>

IntPropertie::IntPropertie(char* title, char* value)
	: Propertie(title, value, (char*)"int")
{
	intValue = value == nullptr ? 0 : atoi(value);
}

int IntPropertie::getIntValue()
{
	return intValue;
}
