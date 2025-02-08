#pragma once
#include "../../Screens/Screen.h"

class PauseMenu :
    public Screen
{
    void Initialize() override;
    void Draw() override;
public:
    void Update() override;
};