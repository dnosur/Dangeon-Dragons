#pragma once
#define SAVE_FILE "Content/save"

#include "Window.h"

#include "figures/Rect.h"

#include "Figures.h"
#include "WindowPointerController.h"

#include "tiny/TinyXml.h"

#include "GameStatuses.h"
#include "animator/SpriteAnimation.h"
#include "camera/Camera.h"

class MainWindow :
    public Window, std::enable_shared_from_this<MainWindow>
{
    GameStatuses gameStatus;

    std::vector<std::pair<std::string, std::string>> saveData;
public:
    MainWindow();
    MainWindow(
        Size size, 
        std::string title, 
        bool fullscreen = false, 
        Color backgroundColor = Color(1, 1, 1), 
        GLFWmonitor* monitor = NULL, 
        GLFWwindow* share = NULL
    );
    ~MainWindow() = default;

    void Initialize() override;
    void Update() override;
};

