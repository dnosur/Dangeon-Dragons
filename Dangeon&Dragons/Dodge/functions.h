#pragma once
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>
#include <gl/glut.h>

#include <Lmcons.h>
#include <iostream>

#include <windows.h>
#include <string>
#include <conio.h>

#include <map>
#include <vector>

#include "Coord.h"
#include "Color.h"
#include "Size.h"

void clear();
void pause();

void gotoxy(int X, int Y);
void gotoxy(COORD coord);

void DrawSymbol(Coord coord, char symbol, Size windowSize, const Color color = Color(1, 0, 0));
void DrawSymbols(Coord coord, char* symbols, Size windowSize, const Color color = Color(1, 0, 0));
void copyStr(char* origin, char*& destination);
void copyStr(const char* origin, char*& destination);

COORD getxy();
void getxy(int& x, int& y);

Size MathSize(Size size, Size windowSize);
Coord MathCoord(Coord coord, Size windowSize);

template <typename T>
void copyArray(T** origin, T** destination);

template <typename T>
void ClearVector(std::vector<T>& vector);

template<typename T>
inline bool ExistInVector(std::vector<T>& vector, T value);

template<typename T>
inline void RemoveFromVector(std::vector<T>& vector, T value);

template<typename T>
inline void copyArray(T** origin, T** destination)
{
	*destination = *origin;
}

template<typename T>
inline void ClearVector(std::vector<T>& vector)
{
	if (vector.size() <= 0) {
		return;
	}
	vector.clear();
	vector.shrink_to_fit();
}

template<typename T>
inline bool ExistInVector(std::vector<T>& vector, T value)
{
	if (vector.empty() || value == nullptr) {
		return false;
	}

	for (T& item : vector) {
		if (item == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
inline void RemoveFromVector(std::vector<T>& vector, T value)
{
	auto it = std::remove(vector.begin(), vector.end(), value);
	vector.erase(it, vector.end());
}

float CalculateDistance(const Coord& a, const Coord& b);

std::string generateRandomString(int length);

const char* GetCurrentUser();
