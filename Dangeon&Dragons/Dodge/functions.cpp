#include "functions.h"

void clear() {
	system("cls");
}

void pause() {
	_getch();
}

void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxy(COORD coord)
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

void copyStr(char* origin, char*& destination)
{
	if (origin == nullptr) {
		return;
	}

	destination = new char[strlen(origin) + 1];
	strcpy_s(destination, strlen(origin) + 1, origin);
}

void copyStr(const char* origin, char*& destination)
{
	if (origin == nullptr) {
		return;
	}

	destination = new char[strlen(origin) + 1];
	strcpy_s(destination, strlen(origin) + 1, origin);
}

void getxy(int& x, int& y) {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	x = screenBufferInfo.dwCursorPosition.X;
	y = screenBufferInfo.dwCursorPosition.Y;
}
//
//const int newX = static_cast<int>((float)(element.first.GetPos().X - 15.0f) * (float)(window->GetSize().width / 1280.0f));
//const int newY = static_cast<int>((float)(element.first.GetPos().Y + .0f) * (float)(window->GetSize().height / 720.0f));
//
//const int sizeWidth = static_cast<int>(50.0f * (float)(window->GetSize().width / 1280.0f));
//const int sizeHeight = static_cast<int>(50.0f * (float)(window->GetSize().height / 720.0f));

Size MathSize(Size size, Size windowSize)
{
	return Size(
		static_cast<int>((float)(size.width * (float)(windowSize.width / 1280.0f))),
		static_cast<int>((float)(size.height * (float)(windowSize.height / 720.0f)))
	);
}

Coord MathCoord(Coord coord, Size windowSize)
{
	return Coord(
			static_cast<int>((float)(coord.X * (float)(windowSize.width / 1280.0f))),
			static_cast<int>((float)(coord.Y * (float)(windowSize.height / 720.0f)))
	);
}

float CalculateDistance(const Coord& a, const Coord& b)
{
	float dx = a.X - b.X;
	float dy = a.Y - b.Y;
	return std::sqrt(dx * dx + dy * dy);
}

const char* GetCurrentUser()
{
	wchar_t username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);

	char* username_char = new char[username_len];
	wcstombs(username_char, username, username_len);

	return username_char;
}

COORD getxy() {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());

	return screenBufferInfo.dwCursorPosition;
}