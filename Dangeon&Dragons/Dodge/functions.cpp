#include "functions.h"

#include "IGameObject.h"
#include "raycast/Ray.h"

#include <random>
#include "raycast/Raycast.h"
#include "collisions/PoligonCollision.h"
#include "collisions/BoxCollision.h"

void Clear() {
	system("cls");
}

void Pause() {
	_getch();
}

void GoToXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GoToXY(COORD coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawSymbol(Coord coord, char symbol, Size windowSize, const Color color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowSize.GetWidth(), windowSize.GetHeight(), 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);

	glRasterPos2f(coord.X, coord.Y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, symbol);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void DrawSymbols(Coord coord, char* symbols, Size windowSize, const Color color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, windowSize.GetWidth(), windowSize.GetHeight(), 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);

	glRasterPos2f(coord.X, coord.Y);


	while (*symbols) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *symbols);
		symbols++;
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void CopyStr(char* origin, char*& destination)
{
	if (origin == nullptr) {
		return;
	}

	destination = new char[strlen(origin) + 1];
	strcpy_s(destination, strlen(origin) + 1, origin);
}

void CopyStr(const char* origin, char*& destination)
{
	if (origin == nullptr) {
		return;
	}

	destination = new char[strlen(origin) + 1];
	strcpy_s(destination, strlen(origin) + 1, origin);
}

void GetXY(int& x, int& y) {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	x = screenBufferInfo.dwCursorPosition.X;
	y = screenBufferInfo.dwCursorPosition.Y;
}

Size MathSize(Size size, Size windowSize)
{
	return Size(
		static_cast<int>((float)(size.width * (float)(windowSize.width / DEFAULT_WINDOW_WIDTH))),
		static_cast<int>((float)(size.height * (float)(windowSize.height / DEFAULT_WINDOW_HEIGHT)))
	);
}

Coord MathCoord(Coord coord, Size windowSize)
{
	return Coord(
		static_cast<int>((float)(coord.X * (float)(windowSize.width / DEFAULT_WINDOW_WIDTH))),
		static_cast<int>((float)(coord.Y * (float)(windowSize.height / DEFAULT_WINDOW_HEIGHT)))
	);
}

float CalculateDistance(Coord a, Coord b)
{
	return CalculateDistanceRef(a, b);
}

float CalculateDistanceRef(Coord& a, Coord& b)
{
	float dx = a.X - b.X;
	float dy = a.Y - b.Y;
	return std::sqrt(dx * dx + dy * dy);
}

float CalculateDistanceWithSize(Coord a, Coord b, Size bSize)
{
	float deltaX = a.X - b.X;
	float deltaY = a.Y - b.Y;

	float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

	float radius = std::sqrt(bSize.width * bSize.width + bSize.height * bSize.height) / 2.0f;

	float adjustedDistance = distance - radius;

	return std::max(0.0f, adjustedDistance);
}

bool IsPointBetween(Coord start, Coord end, Coord point)
{
	float vectorX = end.X - start.X;
	float vectorY = end.Y - start.Y;

	float pointVectorX = point.X - start.X;
	float pointVectorY = point.Y - start.Y;

	float dotProduct = pointVectorX * vectorX + pointVectorY * vectorY;

	float lengthSquared = vectorX * vectorX + vectorY * vectorY;

	return dotProduct >= 0 && dotProduct <= lengthSquared;
}

bool IsPointBetween(Coord start, Coord end, Coord point, float tolerance)
{
	float area = std::abs(
		(end.X - start.X) * (start.Y - point.Y) -
		(start.X - point.X) * (end.Y - start.Y)
	) / 2.0f;

	float lineLength = CalculateDistance(start, end);

	float distance = (2 * area) / lineLength;

	return distance <= tolerance && IsPointBetween(start, end, point);
}

bool IsPointBetween(Ray* ray, Coord point)
{
	float vectorX = ray->direction->X - ray->origin->X;
	float vectorY = ray->direction->Y - ray->origin->Y;

	float pointVectorX = point.X - ray->origin->X;
	float pointVectorY = point.Y - ray->origin->Y;

	float dotProduct = pointVectorX * vectorX + pointVectorY * vectorY;

	float lengthSquared = vectorX * vectorX + vectorY * vectorY;

	return dotProduct >= 0 && dotProduct <= lengthSquared;
}

bool IsPointBetween(std::unique_ptr<Ray>& ray, Coord point)
{
	float vectorX = ray->direction->X - ray->origin->X;
	float vectorY = ray->direction->Y - ray->origin->Y;

	float pointVectorX = point.X - ray->origin->X;
	float pointVectorY = point.Y - ray->origin->Y;

	float dotProduct = pointVectorX * vectorX + pointVectorY * vectorY;

	float lengthSquared = vectorX * vectorX + vectorY * vectorY;

	return dotProduct >= 0 && dotProduct <= lengthSquared;
}

bool IsObjectBetween(Ray* ray, IGameObject* object, bool useCollision) {

	// Êîîðäèíàòû ëó÷à
	Coord rayOrigin = *ray->origin;
	Coord rayEnd = *ray->direction;
	Coord rayDir = { rayEnd.X - rayOrigin.X, rayEnd.Y - rayOrigin.Y, rayEnd.Z - rayOrigin.Z };

	// Íîðìàëèçóåì âåêòîð íàïðàâëåíèÿ ëó÷à
	double magnitude = std::sqrt(rayDir.X * rayDir.X + rayDir.Y * rayDir.Y + rayDir.Z * rayDir.Z);
	if (magnitude == 0) {
		return false; // Íåêîððåêòíîå íàïðàâëåíèå
	}
	rayDir.X /= magnitude;
	rayDir.Y /= magnitude;
	rayDir.Z /= magnitude;

	if (useCollision) {
		if (std::shared_ptr<PoligonCollision> collision = std::dynamic_pointer_cast<PoligonCollision>(object->GetCollision().lock())) {
			std::vector<Coord> polygonPoints = collision->GetPoints();

			// Ïðîâåðÿåì ïåðåñå÷åíèå ëó÷à ñ ìíîãîóãîëüíèêîì
			return Raycast::CheckRayPolygonIntersection(rayOrigin, rayDir, polygonPoints);
		}
	}

	// Ïîëó÷àåì ïîçèöèþ è ðàçìåðû îáúåêòà
	Coord objPos = object->GetPos();
	Size objSize = object->GetSize();

	if (useCollision) {
		std::shared_ptr<BoxCollision> collision = std::dynamic_pointer_cast<BoxCollision>(
			object->GetCollision().lock()
		);

		objPos = (collision != nullptr ? collision->GetPoints()[0] : objPos);
		objSize = (collision != nullptr ? collision->GetSize() : objSize);
	}

	// Âû÷èñëÿåì AABB îáúåêòà
	double objLeft = objPos.X;
	double objRight = objPos.X + objSize.width;
	double objBottom = objPos.Y + objSize.height;
	double objTop = objPos.Y;

	if ((rayOrigin.X > objRight + ray->rayWidth && rayEnd.X > objRight + ray->rayWidth) ||
		(rayOrigin.X < objLeft - ray->rayWidth && rayEnd.X < objLeft - ray->rayWidth)) {
		return false; // Ëó÷ ïîëíîñòüþ ñïðàâà èëè ñëåâà îò îáúåêòà
	}

	if ((rayOrigin.Y > objBottom + ray->rayWidth && rayEnd.Y > objBottom + ray->rayWidth) ||
		(rayOrigin.Y < objTop - ray->rayWidth && rayEnd.Y < objTop - ray->rayWidth)) {
		return false; // Ëó÷ ïîëíîñòüþ âûøå èëè íèæå îáúåêòà
	}

	object->Draw();
	return true;

	//Ìåòîä AABB íå ïîíàäîáèëñÿ, íî íà áóäóùåå ïóñêàé áóäåò :)

	// Ïðîâåðÿåì ïåðåñå÷åíèå ëó÷à ñ AABB
	return Raycast::CheckRayAABBIntersection(
		rayOrigin, rayDir, ray->rayWidth,
		objLeft, objRight, objBottom, objTop
	);
}

bool IsObjectBetween(std::unique_ptr<Ray>& ray, std::weak_ptr<IGameObject> object, bool useCollision)
{
	std::shared_ptr<IGameObject> shared_obj = object.lock();
	if (!shared_obj) {
		return false;
	}

	// Êîîðäèíàòû ëó÷à
	Coord rayOrigin = *ray->origin;
	Coord rayEnd = *ray->direction;
	Coord rayDir = { rayEnd.X - rayOrigin.X, rayEnd.Y - rayOrigin.Y, rayEnd.Z - rayOrigin.Z };

	// Íîðìàëèçóåì âåêòîð íàïðàâëåíèÿ ëó÷à
	double magnitude = std::sqrt(rayDir.X * rayDir.X + rayDir.Y * rayDir.Y + rayDir.Z * rayDir.Z);
	if (magnitude == 0) {
		return false; // Íåêîððåêòíîå íàïðàâëåíèå
	}
	rayDir.X /= magnitude;
	rayDir.Y /= magnitude;
	rayDir.Z /= magnitude;

	if (useCollision) {
		if (std::shared_ptr<PoligonCollision> collision = std::dynamic_pointer_cast<PoligonCollision>(shared_obj->GetCollision().lock())) {
			std::vector<Coord> polygonPoints = collision->GetPoints();

			// Ïðîâåðÿåì ïåðåñå÷åíèå ëó÷à ñ ìíîãîóãîëüíèêîì
			return Raycast::CheckRayPolygonIntersection(rayOrigin, rayDir, polygonPoints);
		}
	}

	// Ïîëó÷àåì ïîçèöèþ è ðàçìåðû îáúåêòà
	Coord objPos = shared_obj->GetPos();
	Size objSize = shared_obj->GetSize();

	if (useCollision) {
		std::shared_ptr<BoxCollision> collision = std::dynamic_pointer_cast<BoxCollision>(
			shared_obj->GetCollision().lock()
		);

		objPos = (collision != nullptr ? collision->GetPoints()[0] : objPos);
		objSize = (collision != nullptr ? collision->GetSize() : objSize);
	}

	// Âû÷èñëÿåì AABB îáúåêòà
	double objLeft = objPos.X;
	double objRight = objPos.X + objSize.width;
	double objBottom = objPos.Y + objSize.height;
	double objTop = objPos.Y;

	if ((rayOrigin.X > objRight + ray->rayWidth && rayEnd.X > objRight + ray->rayWidth) ||
		(rayOrigin.X < objLeft - ray->rayWidth && rayEnd.X < objLeft - ray->rayWidth)) {
		return false; // Ëó÷ ïîëíîñòüþ ñïðàâà èëè ñëåâà îò îáúåêòà
	}

	if ((rayOrigin.Y > objBottom + ray->rayWidth && rayEnd.Y > objBottom + ray->rayWidth) ||
		(rayOrigin.Y < objTop - ray->rayWidth && rayEnd.Y < objTop - ray->rayWidth)) {
		return false; // Ëó÷ ïîëíîñòüþ âûøå èëè íèæå îáúåêòà
	}

	shared_obj->Draw();
	return true;

	//Ìåòîä AABB íå ïîíàäîáèëñÿ, íî íà áóäóùåå ïóñêàé áóäåò :)

	// Ïðîâåðÿåì ïåðåñå÷åíèå ëó÷à ñ AABB
	return Raycast::CheckRayAABBIntersection(
		rayOrigin, rayDir, ray->rayWidth,
		objLeft, objRight, objBottom, objTop
	);
}

std::string GenerateRandomString(int length)
{
	const std::string characters =
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> distribution(0, characters.size() - 1);

	std::string randomString;
	randomString.reserve(length);

	for (int i = 0; i < length; ++i) {
		randomString += characters[distribution(generator)];
	}

	return randomString;
}

std::string GetCurrentUser()
{
	wchar_t username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);

	char* username_char = new char[username_len];
	wcstombs(username_char, username, username_len);

	return username_char;
}

COORD GetXY() {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	return screenBufferInfo.dwCursorPosition;
}