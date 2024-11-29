#pragma once
#include "Propertie.h"

#include <string>

class StringPropertie :
    public Propertie
{
public:
	StringPropertie(char* name, char* value);

	std::string getStrValue();
};

