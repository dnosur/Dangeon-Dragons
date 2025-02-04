#include "MainWindow.h"
#include "font/Font.h"
#include "Save.h"

#include "./images/SlicedImage.h"

#include "../Content/Scripts/Maps/WonderWorld/WonderWold.h"
#include "../Content/Scripts/Characters/Player/Player.h"
#include "../Content/Scripts/Characters/Enemys/Skeleton.h"

#include "../Dodge/GameObjects.h"
#include "../Content/Scripts/UI/HpBar/HpBar.h"

MainWindow::MainWindow(): Window()
{
    gameStatus = GameStatuses::End;
}

MainWindow::MainWindow(Size size, std::string title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
    Window(size, title, backgroundColor, monitor, share) {
    gameStatus = GameStatuses::Stop;
}

MainWindow::~MainWindow()
{
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

    images.Load("Content/Images/Background/ground.png", "ground");

    //std::string sample = "123";
    //std::unique_ptr<std::string> title;
    //title.reset(&sample);

    WindowPointerController::SetPointer(window, WindowPointer<Mouse>("Mouse", &mouse));
    WindowPointerController::SetPointer(window, WindowPointer<Keyboard>("Keyboard", &keyboard));

    WindowPointerController::SetPointer(window, WindowPointer<AudioController>("audioController", &audioController));

    WindowPointerController::SetPointer(window, WindowPointer<Window>("MainWindow", this));

    WindowPointerController::SetPointer(window, WindowPointer<GameStatuses>("GameStatus", &gameStatus));

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
       WindowPointerController::GetValue<Window>(window, "MainWindow")->GetValue().ResizeWindow(Size(width, height));
    });
}

void MainWindow::Update()
{
    gameStatus = GameStatuses::Start;

    std::unique_ptr<WonderWold> wonderWold = std::make_unique<WonderWold>(
        this, 
        TinyXml::LoadMap(
            "Content/Maps/world/world.tmx", 
            "wonder_world"
        ),
        Coord(100, -400)
    );

    std::vector<std::weak_ptr<IGameObject>> solidCollisions = wonderWold->GetClassesByType("SolidCollision");

    if (!solidCollisions.empty()) {
        WindowPointerController::SetPointer(
            window, 
            WindowPointer<std::vector<std::weak_ptr<IGameObject>>>(
                "SolidCollisions", &solidCollisions
            )
        );
    }

    std::unique_ptr<Font> sampleFont = std::make_unique<Font>(
        "NotJamGlasgow",
        "Content/Fonts/Not Jam Glasgow 13/Not Jam Glasgow 16.ttf",
        GetSize()
    );

   GameObjects::Add(&solidCollisions);

    std::unique_ptr<HpBar> hpBar = std::make_unique<HpBar>(*this);

    bool down = false;

    while (!glfwWindowShouldClose(GetWindow()) && !IsClosed())
    {
        FillBackground();
        glClear(GL_COLOR_BUFFER_BIT);

        //glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (gameStatus == GameStatuses::Restart) {
        }

        images.DrawImage(
            "ground",
            Coord(0, 0),
            GetSize(),
            GetSize(),
            Color(0.4f, 0.4f, 0.4f)
        );

        if (gameStatus == GameStatuses::End) {
        }

        wonderWold->Update();
        hpBar->Update();

        sampleFont->RenderText("Work in progress", Coord(30, 30), 4.0f, Color(1.0f, .0f, .0f, .5f));

        mouse.Update();
        keyboard.Update();

        //Debug();  // ������� ������

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    CloseWindow();
}
