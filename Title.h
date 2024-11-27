#pragma once

#include"BaseScene.h"
#include "Camera.h"

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
    Camera* camera = NULL;
};

