#pragma once
#include "Input.h"
#include "BlackOut.h"
#include"BaseScene.h"

class Result : public BaseScene
{
public:

    Result(SceneManager& manager);
    ~Result();

    void Initialize();
    void Update();
    void Draw();

private:
    int clear_font;
    int font_back;
    Input* input;
    BlackOut* blackOut;
};

