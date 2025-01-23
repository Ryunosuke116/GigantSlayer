#pragma once
#include "Input.h"
#include "BlackOut.h"
#include"BaseScene.h"

class GameClear : public BaseScene
{
public:

    GameClear(SceneManager& manager);
    ~GameClear();

    void Initialize();
    void Update();
    void Draw();

private:
    int clear_font;
    int font_back;
    int titleBack_font;
    Input* input;
    BlackOut* blackOut;
};

