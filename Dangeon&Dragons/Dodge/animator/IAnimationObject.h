#pragma once
#include <string>

#include "../Coord.h"
#include "../Size.h"

__interface IAnimationObject
{
    bool setFloat(const std::string& propertyName, float value);
    bool setBool(const std::string& propertyName, bool value);
    bool setInt(const std::string& propertyName, int value);
    bool setCoord(const std::string& propertyName, Coord value);
    bool setSize(const std::string& propertyName, Size value);

    bool getFloat(const std::string& propertyName, float& outValue);
    bool getBool(const std::string& propertyName, bool& outValue);
    bool getInt(const std::string& propertyName, int& outValue);
    bool getCoord(const std::string& propertyName, Coord& outValue);
    bool getSize(const std::string& propertyName, Size& outValue);
};