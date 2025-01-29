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

struct Ray;

__interface IGameObject;

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
inline bool ExistInVector(std::vector<T>& vector, T* value);

template<typename T>
inline void RemoveFromVector(std::vector<T>& vector, T value);

template <typename T>
inline bool ValidateVectorIndex(std::vector<T>& vector, int index);

template <typename T>
T Max(T a, T b);

template <typename T>
T Min(T a, T b);

template <typename T, typename T1>
bool EqualTypes(T* a, T1* b);

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

template<typename T>
inline bool ValidateVectorIndex(std::vector<T>& vector, int index)
{
	if (index < 0 || index >= vector.size()) {
		return false;
	}
	return true;
}

template<typename T>
inline T Max(T a, T b)
{
	return (a > b) ? a : b;
}

template<typename T>
inline T Min(T a, T b)
{
	return (a < b) ? a : b;
}

template<typename T, typename T1>
inline bool EqualTypes(T* a, T1* b)
{
	T* bPtr = dynamic_cast<T*>(&b);
	T1* aPtr = dynamic_cast<T1*>(&a);

	return bPtr != nullptr && aPtr != nullptr;
}

float CalculateDistance(const Coord a, const Coord b);
float CalculateDistanceRef(const Coord& a, const Coord& b);

float CalculateDistanceWithSize(Coord a, Coord b, Size bSIze);

bool IsPointBetween(Coord start, Coord end, Coord point);

bool IsPointBetween(Coord start, Coord end, Coord point, float tolerance);

bool IsPointBetween(Ray* ray, Coord point);

/**
 * Checks if an object is between a ray.
 *
 * @param ray The ray to check.
 * @param object The object to check.
 * @param useCollision Whether to use collision or not.
 *
 * @return True if the object is between the ray, false otherwise.
 */
bool IsObjectBetween(Ray* ray, IGameObject* object, bool useCollision = true);

std::string generateRandomString(int length);

<<<<<<< Updated upstream
const char* GetCurrentUser();
=======
std::string GenerateRandomString(int length);

std::string GetCurrentUser();
>>>>>>> Stashed changes
