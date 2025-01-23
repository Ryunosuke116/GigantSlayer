#pragma once

#include"BaseScene.h"
#include "Input.h"
#include "Camera.h"
#include "BlackOut.h"

class Title :public BaseScene
{
public:

    Title(SceneManager& manager);
    ~Title();

    void Initialize();
    void Update();
    void Draw();
private:
    int titleHandle;
    int backGroundHandle;
    int start_font;
    int alpha;
    int addAlpha;
    int alpha_bright;
    bool isPush;
    Camera* camera = NULL;
    Input* input = NULL;
    BlackOut* blackOut = NULL;
};

