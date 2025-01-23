#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include "Player.h"

class GameUI
{
private:
    int enemyHPBar_front;
    int HPBar_back;
    int enemyHPBar_name;
    int playerHandle;
    int playerHPBer_back;
    int playerHPBar_front;
    int playerHPBar_back;
    int gameOver_back;
    int died_font;
    int start_font;
    int X_button;
    int A_button;

    int shadow;
    int alpha_back;
    int alpha_front;
    int alpha_bright;
    int alpha_UI;
    double shake;
    float oldHP_enemy;
    float oldHP_player;
    float drawHP_enemy;
    float drawHP_player;
    static constexpr float maxDrawHP_enemy = 1000;
    static constexpr float mindrawHP_enemy = 300;
    static constexpr float maxDrawHP_player = 208;

public:

    GameUI();
    ~GameUI();

    void Initialize(Enemy& enemy, Player& player);
    void Update(Enemy& enemy, Player& player, bool isChange);
    void Draw();

    void EnemyHPUpdate(Enemy& enemy);
    void PlayerHPUpdate(Player& player);
    void WhenGameOver_Draw();

    int GetAlpha_bright() { return alpha_bright; }

};

