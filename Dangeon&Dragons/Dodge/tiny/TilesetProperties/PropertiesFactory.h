#pragma once
#include "BoolPropertie.h"
#include "StringPropertie.h"
#include "IntPropertie.h"

static class PropertiesFactory
{
public:
	static BoolPropertie* createBoolPropertie(char* title, char* value, char* type);

	static StringPropertie* createStringPropertie(char* title, char* value, char* type);

	static IntPropertie* createIntPropertie(char* title, char* value, char* type);

	static Propertie* createPropertie(char* title, char* value, char* type);
};
