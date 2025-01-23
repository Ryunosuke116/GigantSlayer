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
#include "EnemyManager.h"
#include"Common.h"
#include"GameUI.h"
#include"BlackOut.h"
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
    void SceneChanger(Player& player, Enemy& enemy, Camera& camera,GameUI& gameUI);
private:
    static constexpr int objectNumber = 4;      //オブジェクトの数
    int alpha;
    //定義
    Input* input = NULL;
    Effect* effect = NULL;
    Player* player = NULL;
    Camera* camera = NULL;
    Map* map = NULL;
    Calculation* calculation = NULL;
    EnemyManager* enemyManager = NULL;
    std::array<Object*, objectNumber> object = {
       NULL,
       NULL,
       NULL,
       NULL
    };
    Enemy* enemy = NULL;
    Common* common = NULL;
    GameUI* gameUI = NULL;
    ObjectManager* objectManager = NULL;
    BlackOut* blackOut = NULL;
};

