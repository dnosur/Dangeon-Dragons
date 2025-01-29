#pragma once
#include "Propertie.h"

#include <string>

class StringPropertie :
    public Propertie
{
public:
	StringPropertie(std::string title, std::string value);

	std::string getStrValue();
};

