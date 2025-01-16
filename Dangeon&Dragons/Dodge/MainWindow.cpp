#include "MainWindow.h"
#include "font/Font.h"
#include "Save.h"

#include "./images/SlicedImage.h"

#include "../Content/Scripts/Maps/WonderWorld/WonderWold.h"
#include "../Content/Scripts/Characters/Player/Player.h"
#include "../Content/Scripts/Characters/Enemys/Skeleton.h"

#include "../Dodge/GameObjects.h"

MainWindow::MainWindow(): Window()
{
    gameStatus = GameStatuses::End;
}

MainWindow::MainWindow(Size size, const char* title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
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

    images.Load("Content/Images/Background/ground.png", "ground");

    //const char* sample = "123";
    //std::unique_ptr<const char*> title;
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

<<<<<<< Updated upstream
    std::unique_ptr<WonderWold> wonderWold = std::unique_ptr<WonderWold>(new WonderWold(
        this,
=======
    std::unique_ptr<WonderWold> wonderWold = std::make_unique<WonderWold>(
        this, 
>>>>>>> Stashed changes
        TinyXml::LoadMap(
            "Content/Maps/world/world.tmx",
            "wonder_world"
        ),
        Coord(100, -400)
    ));

    std::vector<IGameObject*> solidCollisions = wonderWold.get()->GetClassesByType("SolidCollision");

    if (!solidCollisions.empty()) {
        WindowPointerController::SetPointer(window, WindowPointer<std::vector<IGameObject*> >("SolidCollisions", &solidCollisions));
    }

    GameObjects::Add(&solidCollisions);

  //  int *temp = new int(1);
  //  std::weak_ptr<int> target;

  //  {
  //      std::unique_ptr<int> sample_ptr = std::unique_ptr<int>(temp);
		//target = std::weak_ptr<int>(std::shared_ptr<int>(sample_ptr.get()));
  //      std::cout << target.lock() << std::endl;
  //  }

  //  std::cout << target.lock() << std::endl;

    while (!glfwWindowShouldClose(GetWindow()) && !IsClosed())
    {
        FillBackground();
        glClear(GL_COLOR_BUFFER_BIT);

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

        wonderWold.get()->Update();

        mouse.Update();
        keyboard.Update();

        //Debug();  // ֲûגמהטל סטלגמכ

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    wonderWold.release();
    CloseWindow();
}
