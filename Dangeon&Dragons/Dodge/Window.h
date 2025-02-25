#pragma once
#define DEFAULT_WINDOW_WIDTH 1280.0f
#define DEFAULT_WINDOW_HEIGHT 720.0f

#include "./images/ImagesController.h"
#include "./audio/AudioController.h"
#include "./keyboard/Keyboard.h"

#include "GameStatuses.h"

#include "Size.h"
#include "Mouse.h"
#include "Color.h"
#include "Timer.h"

class Camera;

class Window
{
protected:
	static GLFWwindow* window;
	GLFWmonitor* monitor;
	GLFWwindow* share;

	static GameStatuses gameStatus;

	static std::shared_ptr<ImagesController> images;
	static std::shared_ptr<AudioController> audioController;

	static std::shared_ptr<Mouse> mouse;
	static std::shared_ptr<Keyboard> keyboard;

	static std::shared_ptr<Camera> mainCamera;

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

	static GLFWwindow* GetWindow();
	GLFWmonitor* GetMonitor();
	GLFWwindow* GetShare();

	static const Size& GetSizeView();
	static Size GetSize();
	static const Size& GetRenderResolutionView();
	static Size GetRenderResolution();

	static const GameStatuses& GetGameStatus();

	static std::weak_ptr<Camera> GetCamera();
	static void SetCamera(std::unique_ptr<Camera> camera);

	std::string GetTitle();

	virtual void Initialize();
	virtual void Update();

	void MakeContext();

	void CloseWindow();
	const bool IsClosed();

	static float PixelToGLX(float pixelX);
	static float PixelToGLY(float pixelY);

	static float GLXToPixel(float glx);
	static float GLYToPixel(float gly);

	void SetBackgroundColor(Color color);
	Color GetBackgroundColor();

	static std::weak_ptr<ImagesController> GetImagesController();

	static std::weak_ptr<AudioController> GetAudioController();

	static void ResizeWindow(Size size);

	static std::weak_ptr<Mouse> GetMouse();
	static std::weak_ptr<Keyboard> GetKeyboard();

	const GLFWvidmode* GetVideoMode();

	Timer& GetTimer();

	void Debug(bool norm = false);
};