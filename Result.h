#pragma once

#include"BaseScene.h"

class Result : public BaseScene
{
public:

    Result(SceneManager& manager);
    ~Result();

    void Initialize();
    void Update();
    void Draw();
};

