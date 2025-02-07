#pragma once
#define DEFAULT_WINDOW_WIDTH 1280.0f
#define DEFAULT_WINDOW_HEIGHT 720.0f

#include "./images/ImagesController.h"
#include "./audio/AudioController.h"

#include "Size.h"
#include "Mouse.h"
#include "Color.h"
#include "./keyboard/Keyboard.h"
#include "Timer.h"

class Window
{
protected:
	GLFWwindow* window;
	GLFWmonitor* monitor;
	GLFWwindow* share;

	std::shared_ptr<ImagesController> images;
	std::shared_ptr<AudioController> audioController;

	std::shared_ptr<Mouse> mouse;
	std::shared_ptr<Keyboard> keyboard;

	Timer timer;

	static Size size;
	static Size renderResolution;

	Color backgroundColor;

	std::string title;
	bool closed;

	bool fullscreen;

	void MakeWindow();

	void FillBackground();
public:

	Window();
	Window(
		Size size, 
		std::string title,
		bool fullscreen = false,
		Color backgroundColor = Color(1, 1, 1), 
		GLFWmonitor* monitor = NULL, 
		GLFWwindow* share = NULL
	);
	~Window() = default;

	GLFWwindow* GetWindow();
	GLFWmonitor* GetMonitor();
	GLFWwindow* GetShare();

	static const Size& GetSizeView();
	static Size GetSize();
	static const Size& GetRenderResolutionView();
	static Size GetRenderResolution();
	std::string GetTitle();

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
	std::weak_ptr<ImagesController> GetImagesController();

	void ResizeWindow(Size size);

	std::weak_ptr<Mouse> GetMouse();
	std::weak_ptr<Keyboard> GetKeyboard();

	const GLFWvidmode* GetVideoMode();

	Timer& GetTimer();

	void Debug(bool norm = false);
};