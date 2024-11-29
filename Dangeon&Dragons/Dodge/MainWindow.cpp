#include "MainWindow.h"
#include "font/Font.h"
#include "Save.h"

void MainWindow::Lose()
{
    DrawSymbols(
        Coord((GetSize().width / 2) - 50, GetSize().height / 2), 
        (char*)"You lose!", 
        GetSize(), 
        Color(1, 0, .3f)
    );

    std::string recordStr = isRecord 
        ? "New Record: " + std::to_string(record) 
        : "Old Record: " + std::to_string(record);

    DrawSymbols(
        Coord((GetSize().width / 2) - 50, (GetSize().height / 2) + 40),
        (char*)recordStr.c_str(),
        GetSize(),
        isRecord 
            ? Color(0.9f, 0.8f, .3f)
            : Color(.6f, .8f, .2f)
    );

    restartButton->Update();
    restartButtonAnimation.Play();

    if (restartButton->MouseClick(mouse)) {
        std::cout << "Click restart!\n";
    }
}

void MainWindow::Restart()
{
    isRecord = false;
    gameStatus = GameStatuses::Start;
}

void MainWindow::DrawScore(int score)
{
    isRecord = score > record;
    std::string score_str = "Score: " + std::to_string(score);

    DrawSymbols(
        Coord(40, 30), 
        (char*)score_str.c_str(), 
        GetSize(), 
        isRecord 
            ? Color(0.85f, 0.78f, .3f) 
            : Color(.7f, .6f, .1f)
    );

    if (!isRecord && record != 0) {
        std::string record_str = "Record: " + std::to_string(record);
        DrawSymbols(
            Coord(40, 60),
            (char*)record_str.c_str(),
            GetSize(),
            Color(0.85f, 0.78f, .3f)
        );
    }
}

MainWindow::MainWindow(): Window()
{
}

MainWindow::MainWindow(Size size, const char* title, Color backgroundColor, GLFWmonitor* monitor, GLFWwindow* share):
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

    images.Load("Content/Images/Background/ground.png", "ground");

    audioController.Load(Audio("eat", "Content/Sounds/eat.wav"));
    audioController.Load(Audio("lose", "Content/Sounds/lose.wav"));
    audioController.Load(Audio("hit", "Content/Sounds/hit.wav"));

    WindowPointerController::SetPointer(window, WindowPointer<Mouse>("Mouse", &mouse));
    WindowPointerController::SetPointer(window, WindowPointer<Keyboard>("Keyboard", &keyboard));

    WindowPointerController::SetPointer(window, WindowPointer<AudioController>("audioController", &audioController));

    WindowPointerController::SetPointer(window, WindowPointer<Window>("MainWindow", this));

    WindowPointerController::SetPointer(window, WindowPointer<GameStatuses>("GameStatus", &gameStatus));

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
       WindowPointerController::GetValue<Window>(window, "MainWindow")->GetValue().ResizeWindow(Size(width, height));
    });

    restartButton = new Rect(
        "RestartButton",
        *this,
        Coord(GetSize().width / 2, (GetSize().height / 2) - 100),
        Size(120, 120),
        Color(1, 1, 1)
    );

    restartButton->GetMaterial()->SetDiffuseMap(new Image());
    restartButton->HookMouseClick([](IGameObject* object, GLFWwindow* window) {
        WindowPointer<GameStatuses>* gameStatus = WindowPointerController::GetValue<GameStatuses>(window, "GameStatus");
        if (!gameStatus) {
            return;
        }

        gameStatus->GetValue() = GameStatuses::Restart;
    });

    restartButtonAnimation = SpriteAnimation(
        "RestartButtonAnimation",
        "Content/Animations/RestartButtonAnimtion",
        4,
        this
    );

    restartButtonAnimation.SetRepeat(true);
    restartButtonAnimation.SetRootTile(restartButton->GetMaterial()->GetDiffuseMap());


    saveData = Save::LoadData(SAVE_FILE);
    for (int i = 0; i < saveData.size(); i++) {
        if (saveData[i].first == "User" && saveData[i].second == GetCurrentUser()) {
            if (i + 1 >= saveData.size()) {
                record = 0;
                break;
            }

			if (saveData[i + 1].first == "Record") {
                recordFieldIndex = i + 1;
				record = std::stoi(saveData[i + 1].second);
                break;
			}
		}
    }

    isRecord = false;
}

void MainWindow::Update()
{
    gameStatus = GameStatuses::Start;

    while (!glfwWindowShouldClose(GetWindow()) && !IsClosed())
    {
        FillBackground();
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (gameStatus == GameStatuses::Restart) {
            Restart();
        }

        images.DrawImage(
            "ground",
            Coord(0, 0),
            GetSize(),
            GetSize(),
            Color(0.4f, 0.4f, 0.4f)
        );


        if (gameStatus == GameStatuses::End) {
            Lose();
        }

        mouse.Update();
        keyboard.Update();

        //Debug();  // ֲûגמהטל סטלגמכ

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }

    CloseWindow();
}
