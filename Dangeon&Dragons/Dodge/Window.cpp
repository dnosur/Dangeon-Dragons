#include "Window.h"

#include "camera/Camera.h"
#include "MainWindow.h"
#include "audio/SoundSystem.h"

GLFWwindow* Window::window = nullptr;

Size Window::size;
Size Window::renderResolution = Size(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

std::shared_ptr<ImagesController> Window::images = nullptr;
std::shared_ptr<AudioController> Window::audioController = nullptr;

std::shared_ptr<Mouse> Window::mouse = nullptr;
std::shared_ptr<Keyboard> Window::keyboard = nullptr;

std::shared_ptr<Camera> Window::mainCamera = nullptr;

GameStatuses Window::gameStatus;

void Window::MakeWindow()
{
    monitor = glfwGetPrimaryMonitor();

    window = glfwCreateWindow(
        size.width, size.height, 
        title.c_str(), 
        (fullscreen && monitor ? monitor : NULL), 
        share
    );

    if (!window)
    {
        return CloseWindow();
    }

    mouse = std::make_shared<Mouse>(window);
    keyboard = std::make_shared<Keyboard>(window);

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

   Window::size = size;
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

Window::Window(
    Size size, 
    std::string title, 
    bool fullscreen,
    Color backgroundColor, 
    GLFWmonitor* monitor, 
    GLFWwindow* share
)
{
    this->size = size;
    this->title = title;

    this->fullscreen = fullscreen;

    this->share = share;
    this->monitor = monitor;

    this->backgroundColor = backgroundColor;

    images = std::make_shared<ImagesController>();
    audioController = std::make_shared<AudioController>();

    MakeWindow();
}

void Window::Render(
    int& argc,
    char**& argv, 

    Size size, 
    std::string name, 

    bool fullscreen, 
    Color backgroundColor
)
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    setlocale(LC_ALL, "ru");

    srand(time(NULL));
    glutInit(&argc, argv);
    if (!glfwInit())
        return;

    SoundSystem soundSystem;
    std::shared_ptr<Window> main = std::make_shared<MainWindow>(
        Size(1280, 720),
        "Dangeon",
        false,
        Color(.4f, .6f, 0)
    );

    main->MakeContext();
    main->Initialize();
    main->Update();

    _CrtDumpMemoryLeaks();
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

const Size& Window::GetRenderResolutionView()
{
    return renderResolution;
}

Size Window::GetRenderResolution()
{
    return renderResolution;
}

const GameStatuses& Window::GetGameStatus()
{
    return gameStatus;
}

std::weak_ptr<Camera> Window::GetCamera()
{
    return mainCamera;
}

void Window::SetCamera(std::unique_ptr<Camera> camera)
{
    Window::mainCamera = std::move(camera);
}

const Size& Window::GetSizeView()
{
    return size;
}

Size Window::GetSize()
{
    return size;
}

std::string Window::GetTitle()
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

    if (window) {
        glfwDestroyWindow(window);
    }

    if (share) {
        glfwDestroyWindow(share);
    }

    glfwTerminate();
    closed = true;

    return;
}

const bool Window::IsClosed()
{
    return closed;
}

float Window::PixelToGLX(float pixelX) {
    return (pixelX / renderResolution.GetWidth()) * 2.0f - 1.0f;
}

float Window::PixelToGLY(float pixelY) {
    return 1.0f - (pixelY / renderResolution.GetHeight()) * 2.0f;
}

float Window::GLXToPixel(float glx)
{
    return ((glx + 1.0f) / 2.0f) * renderResolution.GetWidth();
}

float Window::GLYToPixel(float gly)
{
    return ((1.0f - (gly + 1.0f) / 2.0f) * renderResolution.GetHeight());
}

void Window::SetBackgroundColor(Color color)
{
    this->backgroundColor = color;
}

Color Window::GetBackgroundColor()
{
    return backgroundColor;
}

std::weak_ptr<ImagesController> Window::GetImagesController()
{
    return images;
}

std::weak_ptr<AudioController> Window::GetAudioController()
{
    return audioController;
}

std::weak_ptr<Mouse> Window::GetMouse()
{
    return mouse;
}

std::weak_ptr<Keyboard> Window::GetKeyboard()
{
    return keyboard;
}

const GLFWvidmode* Window::GetVideoMode()
{
	return glfwGetVideoMode(monitor);
}

Timer& Window::GetTimer()
{
    return timer;
}

void Window::Debug(bool norm)
{
    Coord coord = mouse->GetMouseCoord();
    Coord prev = mouse->GetPrevMouseCoord();

    if (coord == prev) {
        return;
    }

    if (norm) {
        float normMouseX = (coord.X / GetRenderResolution().GetWidth()) * 2.0f - 1.0f;
        float normMouseY = 1.0f - (coord.Y / GetRenderResolution().GetHeight()) * 2.0f;
        std::cout << "X: " << normMouseX << " Y: " << normMouseY << std::endl;
        return;
    }

    if (coord.X < 0 || coord.X > renderResolution.width ||
        coord.Y < 0 || coord.Y > renderResolution.height) {
        return;
    }

    std::cout << "X: " << coord.X << " Y: " << coord.Y << std::endl;
    std::cout << "Prev X: " << prev.X << " Y: " << prev.Y << std::endl;
}
