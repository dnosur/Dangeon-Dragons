#include "PropertiesFactory.h"

BoolPropertie PropertiesFactory::createBoolPropertie(char* title, char* value, char* type)
{
	return BoolPropertie(title, value);
}

StringPropertie PropertiesFactory::createStringPropertie(char* title, char* value, char* type)
{
	return StringPropertie(title, value);
}

Propertie PropertiesFactory::createPropertie(char* title, char* value, char* type)
{
	if (!strcmp(type, "bool")) {
		return createBoolPropertie(title, value, type);
	}

	if (!strcmp(type, "string")) {
		return createStringPropertie(title, value, type);
	}

	return Propertie();
}
