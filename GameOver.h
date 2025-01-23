#pragma once
#include "DxLib.h"
#include "input.h"
#include "BaseScene.h"

class GameOver : public BaseScene
{
public:

    GameOver(SceneManager& manager);
    ~GameOver();

    void Initialize();
    void Update();
    void Draw();

private:

    int continue_font = NULL;
    int titleBack_font = NULL;
    int select;
    Input* input = NULL;
};

