#pragma once

#include "Camera.h"
#include"Effect.h"
#include "Enemy.h"
#include"Object.h"
#include "Input.h"
#include "Player.h"
#include "Game.h"
#include "Result.h"
#include "Title.h"
#include "BaseScene.h"
#include "SceneManager.h"
#include "Map.h"
#include "Calculation.h"
#include "ObjectManager.h"
#include "BulletCalculation.h"
#include <iostream>
#include <array>

class Game : public BaseScene
{
public:

    Game(SceneManager& manager);
    ~Game();

    void Initialize();
    void Update();
    void Draw();
private:
    static constexpr int objectNumber = 4;      //オブジェクトの数
    //定義
    Input* input = NULL;
    Effect* effect = NULL;
    Player* player = NULL;
    Camera* camera = NULL;
    Map* map = NULL;
    Calculation* calculation = NULL;
    BulletCalculation* bulletCalculation = NULL;
    std::array<Object*, objectNumber> object = {
       NULL,
       NULL,
       NULL,
       NULL
    };
    Enemy* enemy = NULL;
};

