#include "MainWindow.h"
#include "font/Font.h"
#include "Save.h"

#include "./images/SlicedImage.h"

#include "../Content/Scripts/Maps/WonderWorld/WonderWold.h"
#include "../Content/Scripts/Characters/Player/Player.h"
#include "../Content/Scripts/Characters/Enemys/Skeleton.h"

#include "../Dodge/GameObjects.h"
#include "../Content/Scripts/UI/ProgressBar/HpBar/HpBar.h"

#include "../Content/Scripts/Screens/MainWindowLoading/MainWindowLoading.h"
#include "threads/Thread.h"
#include "../Content/Scripts/UI/ProgressBar/utilities.h"

MainWindow::MainWindow(): Window()
{
    gameStatus = GameStatuses::End;
}

MainWindow::MainWindow(Size size, std::string title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
    Window(size, title, backgroundColor, monitor, share) {
    gameStatus = GameStatuses::Stop;
}

void MainWindow::Initialize()
{
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    std::cout << GetCurrentUser() << std::endl;

    gameStatus = GameStatuses::Initialize;

    ImagesController::SetDefaultImage(std::make_unique<Image>(
        ImagesController::LoadImg("Content/Images/defaultObj.jpg", "default")
    ));

    images->Load("Content/Images/Background/ground.png", "ground");

    //std::string sample = "123";
    //std::unique_ptr<std::string> title;
    //title.reset(&sample);

    WindowPointerController::SetPointer(WindowPointer<Mouse>("Mouse", mouse));
    WindowPointerController::SetPointer(WindowPointer<Keyboard>("Keyboard", keyboard));

    WindowPointerController::SetPointer(WindowPointer<AudioController>("audioController", audioController));

    WindowPointerController::SetPointer(WindowPointer<Window>("MainWindow", weak_from_this()));

    WindowPointerController::SetPointer(WindowPointer<GameStatuses>("GameStatus", &gameStatus));

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
       WindowPointerController::GetValue<Window>("MainWindow")->GetValue().lock()->ResizeWindow(Size(width, height));
    });
}

void MainWindow::Update()
{
	gameStatus = GameStatuses::Loading;
    std::shared_ptr<MainWindowLoading> mainWindowLoading = std::make_shared<MainWindowLoading>(6);
    std::unique_ptr<WonderWold> wonderWold;

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    auto* loadingContext = glfwCreateWindow(1, 1, "Loading Context", NULL, window);

    Thread loadingThread = Thread("loading", [mainWindowLoading, &wonderWold, this, loadingContext](){
        glfwMakeContextCurrent(loadingContext);
        std::weak_ptr<ProgressBar> progressBar = mainWindowLoading->GetProgressBar();
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

    std::unique_ptr<Font> sampleFont = std::make_unique<Font>(
        "NotJamGlasgow",
        "Content/Fonts/Not Jam Glasgow 13/Not Jam Glasgow 16.ttf",
        GetSize()
    );

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

        if (gameStatus == GameStatuses::Start) {
            images->DrawImage(
                "ground",
                Coord(0, 0),
                GetSize(),
                GetSize(),
                Color(0.4f, 0.4f, 0.4f)
            );

            wonderWold->Update();
            hpBar->Update();

            sampleFont->RenderText("Work in progress", Coord(30, 30), 4.0f, Color(1.0f, .0f, .0f, .5f));

            mouse->Update();
            keyboard->Update();
		}

        //Debug();  // ֲûגמהטל סטלגמכ

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    CloseWindow();
}
