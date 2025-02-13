#include "MainWindow.h"
#include "font/Font.h"
#include "Save.h"

#include "threads/Thread.h"

#include "./images/SlicedImage.h"

#include "font/Fonts.h"

#include "../Content/Scripts/Maps/WonderWorld/WonderWold.h"
#include "../Content/Scripts/Characters/Player/Player.h"
#include "../Content/Scripts/Characters/Enemys/Skeleton.h"

#include "../Dodge/GameObjects.h"
#include "../Content/Scripts/UI/ProgressBar/HpBar/HpBar.h"

#include "../Content/Scripts/Screens/MainWindowLoading/MainWindowLoading.h"
#include "../Content/Scripts/UI/ProgressBar/utilities.h"
#include "../Content/Scripts/UI/PauseMenu/PauseMenu.h"
#include "shaders/ShadersController.h"

typedef void (*GLMaxShaderCompilerThreadsARB_t)(GLuint);

MainWindow::MainWindow(): Window()
{
    gameStatus = GameStatuses::End;
}

MainWindow::MainWindow(Size size, std::string title, bool fullscreen, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
    Window(size, title, fullscreen, backgroundColor, monitor, share) {
    gameStatus = GameStatuses::Stop;
}

void MainWindow::Initialize()
{
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    GLMaxShaderCompilerThreadsARB_t glMaxShaderCompilerThreadsARB =
        (GLMaxShaderCompilerThreadsARB_t)wglGetProcAddress("glMaxShaderCompilerThreadsARB");

    std::cout << GetCurrentUser() << std::endl;

    gameStatus = GameStatuses::Initialize;

    //Shaders

    ShadersController::LoadShader(
        std::move(
            std::make_unique<Shader>(
                "BaseFigure",
                "Dodge/shaders/Test/vertex.vs",
                "Dodge/shaders/Test/fragment.frag"
            )
        )
    );

    ShadersController::LoadShader(
        std::move(
            std::make_unique<Shader>(
                "BaseImage",
                "Dodge/shaders/Image/imageVertex.vs",
                "Dodge/shaders/Image/imageFragment.frag"
            )
        )
    );

    ShadersController::LoadShader(
        std::move(
            std::make_unique<Shader>(
                "BaseFont",
                "Dodge/shaders/Font/vertex.vs",
                "Dodge/shaders/Font/fragment.frag"
            )
        )
    );

    //Images

    ImagesController::SetDefaultImage(std::make_unique<Image>(
        ImagesController::LoadImg("Content/Images/defaultObj.jpg", "default")
    ));

    images->Load("Content/Images/Background/ground.png", "ground");

    //Fonts
    Fonts::LoadFont("NotJamGlasgow", "Content/Fonts/Not Jam Glasgow 13/Not Jam Glasgow 16.ttf", Size(56, 56));
    Fonts::LoadFont("DreiFraktur", "Content/Fonts/Drei Fraktur/DreiFraktur.ttf", Size(24, 24));

    //std::string sample = "123";
    //std::unique_ptr<std::string> title;
    //title.reset(&sample);

    //GL_ARB_parallel_shader_compile 

    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
    if (strstr(extensions, "GL_ARB_parallel_shader_compile")) {
        std::cout << "Parallel shader compilation is supported!\n";
        glMaxShaderCompilerThreadsARB(0);
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
       Window::ResizeWindow(Size(width, height));
    });
}

void MainWindow::Update()
{
	gameStatus = GameStatuses::Loading;
    std::shared_ptr<MainWindowLoading> mainWindowLoading = std::make_shared<MainWindowLoading>(7);
    
    std::unique_ptr<PauseMenu> pauseMenu = std::make_unique<PauseMenu>();

    std::unique_ptr<WonderWold> wonderWold;

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    auto* loadingContext = glfwCreateWindow(1, 1, "Loading Context", NULL, window);

    Thread loadingThread = Thread("loading", [mainWindowLoading, &wonderWold, this, loadingContext](){
        glfwMakeContextCurrent(loadingContext);
        std::weak_ptr<ProgressBar> progressBar = mainWindowLoading->GetProgressBar();
        SetProgressBarValue(progressBar, 0);

        images->Load("Content/Images/PauseMenu/pauseMenu.png", "pauseMenu");

        wonderWold = std::make_unique<WonderWold>(
            this,
            TinyXml::LoadMap(
                "Content/Maps/world/world.tmx",
                "wonder_world",
                progressBar
            ),
            Coord(100, -400)
        );

        std::vector<std::weak_ptr<IGameObject>> solidCollisions = wonderWold->GetClassesByType("SolidCollision");

        if (!solidCollisions.empty()) {
            std::unique_ptr<std::vector<std::shared_ptr<IGameObject>>> solidCollisionsPtr = std::make_unique<std::vector<std::shared_ptr<IGameObject>>>();
            for (std::weak_ptr<IGameObject>& solidCollision : solidCollisions) {
                if (solidCollision.expired() || !solidCollision.lock()) {
                    continue;
                }
				solidCollisionsPtr->push_back(solidCollision.lock());
            }

            WindowPointerController::SetPointer(
                WindowPointer<std::vector<std::shared_ptr<IGameObject>>>(
                    "SolidCollisions", std::move(solidCollisionsPtr)
                )
            );
        }   

        GameObjects::Add(&solidCollisions);
        NextProgressBarValue(progressBar);

        glfwMakeContextCurrent(nullptr);
        glfwFocusWindow(window);
    });
    loadingThread.Detach();

    std::unique_ptr<HpBar> hpBar = std::make_unique<HpBar>(*this);

    bool down = false;

    while (!glfwWindowShouldClose(GetWindow()) && !IsClosed())
    {
        FillBackground();
        glClear(GL_COLOR_BUFFER_BIT);

        //glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (gameStatus == GameStatuses::Loading && mainWindowLoading->GetProgressBar().lock()->IsFinished()) {
			gameStatus = GameStatuses::Start;
            mainWindowLoading.reset();
            glfwMakeContextCurrent(window);
            glfwDestroyWindow(loadingContext);
        }

        if (gameStatus == GameStatuses::Loading) {
            mainWindowLoading->Update();
        }

        if (gameStatus == GameStatuses::Restart) {
        }

        if (gameStatus == GameStatuses::End) {
        }

        if (gameStatus == GameStatuses::Start || gameStatus == GameStatuses::Pause) {
            if (keyboard->GetKeyDown() && 
               !keyboard->GetKeyDown()->clamping &&
                keyboard->Click(KeyboardKeys::Esc)
            ) {
                gameStatus = gameStatus == GameStatuses::Pause 
                    ? GameStatuses::Start 
                    : GameStatuses::Pause;
            }

            images->DrawImage(
                "ground",
                Coord(0, 0),
                GetSize(),
                GetSize(),
                Color(0.4f, 0.4f, 0.4f)
            );

            wonderWold->Update();
            hpBar->Update();

            std::shared_ptr<Camera> camera = NULL;

            if (gameStatus == GameStatuses::Pause) {
                pauseMenu->Update();
            }

            Fonts::GetFont("NotJamGlasgow")->RenderText(
                L"Work in progress",
                Coord(30, 30),
                std::make_unique<FontRenderOptions>(
                    1.0f,
                    .0f,
                    nullptr,
                    nullptr,
                    Color(1.0f, .0f, .0f)
               )
            );

            mouse->Update();
            keyboard->Update();
		}

        //Debug();  // ֲûגמהטל סטלגמכ

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    CloseWindow();
}

std::weak_ptr<MainWindow> MainWindow::GetWeak()
{
    return weak_from_this();
}
