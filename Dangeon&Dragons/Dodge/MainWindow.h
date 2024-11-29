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

class MainWindow :
    public Window
{
    GameStatuses gameStatus;

    SpriteAnimation restartButtonAnimation;
    Rect* restartButton;

    std::vector<std::pair<std::string, std::string>> saveData;
    int recordFieldIndex;

    int record;
    bool isRecord;

    void Lose();
    void Restart();

    void DrawScore(int score);
public:
    MainWindow();
    MainWindow(Size size, const char* title, Color backgroundColor = Color(1, 1, 1), GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

    void Initialize() override;
    void Update() override;
};

