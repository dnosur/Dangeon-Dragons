#pragma once
#define SAVE_FILE "Content/save"

#include "Window.h"

#include "figures/Rect.h"
#include "figures/Triangle.h"
#include "figures/Circle.h"

#include "Figures.h"
#include "WindowPointerController.h"

#include "tiny/TinyXml.h"

#include "GameStatuses.h"
#include "animator/SpriteAnimation.h"
#include "camera/Camera.h"

class MainWindow :
    public Window
{
    GameStatuses gameStatus;

    std::vector<std::pair<std::string, std::string>> saveData;
public:
    MainWindow();
    MainWindow(Size size, std::string title, Color backgroundColor = Color(1, 1, 1), GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
    ~MainWindow();

    void Initialize() override;
    void Update() override;
};

