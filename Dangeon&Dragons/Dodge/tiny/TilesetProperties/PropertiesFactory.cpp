#include "PropertiesFactory.h"

BoolPropertie* PropertiesFactory::createBoolPropertie(char* title, char* value, char* type)
{
	return new BoolPropertie(title, value);
}

StringPropertie* PropertiesFactory::createStringPropertie(char* title, char* value, char* type)
{
	return new StringPropertie(title, value);
}

IntPropertie* PropertiesFactory::createIntPropertie(char* title, char* value, char* type)
{
	return new IntPropertie(title, value);
}

Propertie* PropertiesFactory::createPropertie(char* title, char* value, char* type)
{
	if (!strcmp(type, "bool")) {
		return createBoolPropertie(title, value, type);
	}

	if (!strcmp(type, "string")) {
		return createStringPropertie(title, value, type);
	}

	if (!strcmp(type, "int")) {
		return createIntPropertie(title, value, type);
	}

	return new Propertie();
}
