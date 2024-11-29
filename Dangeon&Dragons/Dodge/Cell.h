#pragma once
#include "Coord.h"

template <typename T>
struct Cell
{
    Cell();
    Cell(Coord coord, T value);

    Coord coord;
    T value;

    bool revealed;
    bool marker;

    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;
    Cell& operator=(const Cell& other);
};

template <typename T>
Cell<T>::Cell() : value(' '), revealed(false), marker(false) {}

template <typename T>
Cell<T>::Cell(Coord coord, T value) :
    coord(coord), value(value),
    revealed(false), marker(false) {}

template <typename T>
bool Cell<T>::operator==(const Cell& other) const
{
    return coord == other.coord && value == other.value &&
        revealed == other.revealed && marker == other.marker;
}

template <typename T>
bool Cell<T>::operator!=(const Cell& other) const
{
    return !(*this == other);
}

template <typename T>
Cell<T>& Cell<T>::operator=(const Cell& other)
{
    if (this != &other)
    {
        coord = other.coord;
        value = other.value;

        revealed = other.revealed;
        marker = other.marker;
    }
    return *this;
}