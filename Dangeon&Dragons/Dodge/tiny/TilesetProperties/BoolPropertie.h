#pragma once
#include "Propertie.h"
#include <string>

class BoolPropertie :
    public Propertie
{
	bool boolValue;
public:
	BoolPropertie(std::string title, std::string value);
	bool getBoolValue();
};

