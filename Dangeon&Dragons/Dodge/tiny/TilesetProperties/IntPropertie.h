#pragma once
#include "Propertie.h"

class IntPropertie :
    public Propertie
{
	int intValue;
public:
	IntPropertie(char* title, char* value);
	int getIntValue();
};

