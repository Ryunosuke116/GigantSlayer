#include "GameUI.h"

/// <summary>
/// インスタンス化
/// </summary>
GameUI::GameUI()
{
    HPBar_back = LoadGraph("material/HPbar_02.png");
    HPBar_front = LoadGraph("material/HPbar_01.png");
    HPBar_name = LoadGraph("material/HPbar_name.png");
}

void GameUI::Initialize(Enemy& enemy)
{
    oldHP = enemy.GetHP();
    drawHP = 1000;
}

void GameUI::Update(Enemy& enemy)
{
    int enemyNowHP = enemy.GetHP();

    if (oldHP > enemyNowHP)
    {
        oldHP--;
        drawHP = maxDrawHP * (oldHP / 100);
    }
}

/// <summary>
/// 描画
/// </summary>
void GameUI::Draw()
{
    DrawExtendGraph(300, -20,1300, 90, HPBar_back, true);
    DrawExtendGraph(300, -20, drawHP + 300, 90, HPBar_front, true);
    DrawExtendGraph(300, -40, 1300, 70, HPBar_name, true);
}