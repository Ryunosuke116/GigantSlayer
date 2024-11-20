#pragma once

#include"BaseScene.h"

class Title :public BaseScene
{
public:

    Title(SceneManager& manager);
    ~Title();

    void Initialize();
    void Update();
    void Draw();
};

