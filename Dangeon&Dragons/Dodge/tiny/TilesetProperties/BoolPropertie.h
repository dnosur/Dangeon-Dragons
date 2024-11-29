#pragma once
#include "Propertie.h"

class BoolPropertie :
    public Propertie
{
	bool boolValue;
public:
	BoolPropertie(char* title, char* value);
	bool getBoolValue();
};

