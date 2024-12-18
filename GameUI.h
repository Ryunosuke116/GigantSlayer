#pragma once
#include "DxLib.h"
#include "Enemy.h"

class GameUI
{
private:
    int HPBar_front;
    int HPBar_back;
    int HPBar_name;
    float oldHP;
    float drawHP;
    static constexpr float maxDrawHP = 1000;
    static constexpr float minDrawHP = 300;
public:

    GameUI();
    ~GameUI();

    void Initialize(Enemy& enemy);
    void Update(Enemy& enemy);
    void Draw();

};

