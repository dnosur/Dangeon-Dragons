#pragma once
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

#include "ImagesController.h"
#include "AudioController.h"

#include "Size.h"
#include "Mouse.h"
#include "Color.h"
#include "Keyboard.h"
#include "Timer.h"

class Window
{
protected:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	GLFWwindow* share;

	ImagesController images;
	AudioController audioController;

	Mouse mouse;
	Keyboard keyboard;

	Timer timer;

	Size size;

	Color backgroundColor;

	char* title;
	bool closed;

	void MakeWindow();

	void FillBackground();
public:

	Window();
	Window(Size size, const char* title, Color backgroundColor = Color(1, 1, 1), GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

	GLFWwindow* GetWindow();
	GLFWmonitor* GetMonitor();
	GLFWwindow* GetShare();

	Size GetSize();
	char* GetTitle();

	virtual void Initialize();
	virtual void Update();

	void MakeContext();

	void CloseWindow();
	const bool IsClosed();

	float PixelToGLX(float pixelX);
	float PixelToGLY(float pixelY);

	float GLXToPixel(float glx);
	float GLYToPixel(float gly);

	void SetBackgroundColor(Color color);
	Color GetBackgroundColor();

	ImagesController& GetImagesController();

	void ResizeWindow(Size size);

	Mouse& GetMouse();
	Keyboard& GetKeyboard();

	Timer& GetTimer();

	void Debug(bool norm = false);
};