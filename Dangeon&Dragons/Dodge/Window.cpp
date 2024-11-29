#include "Window.h"

void Window::MakeWindow()
{
    window = glfwCreateWindow(size.width, size.height, title, monitor, share);
    if (!window)
    {
        return CloseWindow();
    }

    mouse = Mouse(window);
    keyboard = Keyboard(window);

    closed = false;
}

void Window::FillBackground()
{
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void Window::ResizeWindow(Size size)
{
    if (size.width <= 0 || size.height <= 0) {
        return;
    }

    glViewport(0, 0, size.width, size.height);

    this->size = size;
}

Window::Window()
{
	size = Size(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	title = (char*)"Sample Window";

    backgroundColor = Color(255, 255, 255);

    share = NULL;
    monitor = NULL;

    MakeWindow();
}

Window::Window(Size size, const char* title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share)
{
    this->size = size;
    copyStr(title, this->title);

    this->share = share;
    this->monitor = monitor;

    this->backgroundColor = backgroundColor;

    MakeWindow();
}

GLFWwindow* Window::GetWindow()
{
    return window;
}

GLFWmonitor* Window::GetMonitor()
{
    return monitor;
}

GLFWwindow* Window::GetShare()
{
    return share;
}

Size Window::GetSize()
{
    return size;
}

char* Window::GetTitle()
{
    return title;
}

void Window::Initialize()
{
}

void Window::Update()
{
    while (!glfwWindowShouldClose(window) && !IsClosed())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << "1\n";

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    CloseWindow();
}

void Window::MakeContext()
{
    glfwMakeContextCurrent(window);
}

void Window::CloseWindow()
{
    glfwTerminate();
    closed = true;
    return;
}

const bool Window::IsClosed()
{
    return closed;
}

float Window::PixelToGLX(float pixelX) {
    return (pixelX / size.GetWidth()) * 2.0f - 1.0f;
}

float Window::PixelToGLY(float pixelY) {
    return 1.0f - (pixelY / size.GetHeight()) * 2.0f;
}

float Window::GLXToPixel(float glx)
{
    return ((glx + 1.0f) / 2.0f) * size.GetWidth();
}

float Window::GLYToPixel(float gly)
{
    return ((1.0f - (gly + 1.0f) / 2.0f) * size.GetHeight());
}

void Window::SetBackgroundColor(Color color)
{
    this->backgroundColor = color;
}

Color Window::GetBackgroundColor()
{
    return backgroundColor;
}

ImagesController& Window::GetImagesController()
{
    return images;
}

Mouse& Window::GetMouse()
{
    return mouse;
}

Keyboard& Window::GetKeyboard()
{
    return keyboard;
}

Timer& Window::GetTimer()
{
    return timer;
}

void Window::Debug(bool norm)
{
    Coord coord = mouse.GetMouseCoord();
    Coord prev = mouse.GetPrevMouseCoord();

    if (coord == prev) {
        return;
    }

    if (norm) {
        float normMouseX = (coord.X / GetSize().GetWidth()) * 2.0f - 1.0f;
        float normMouseY = 1.0f - (coord.Y / GetSize().GetHeight()) * 2.0f;
        std::cout << "X: " << normMouseX << " Y: " << normMouseY << std::endl;
        return;
    }

    if (coord.X < 0 || coord.X > size.width ||
        coord.Y < 0 || coord.Y > size.height) {
        return;
    }

    std::cout << "X: " << coord.X << " Y: " << coord.Y << std::endl;
    std::cout << "Prev X: " << prev.X << " Y: " << prev.Y << std::endl;
}
