#include "BoolPropertie.h"
#include <string.h>

BoolPropertie::BoolPropertie(char* title, char* value)
	: Propertie(title, value, (char*)"bool")
{
	boolValue = !strcmp(value, "true");
}

bool BoolPropertie::getBoolValue()
{
	return boolValue;
}
