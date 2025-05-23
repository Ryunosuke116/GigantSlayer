#include "Include.h"

/// <summary>
/// インスタンス化
/// </summary>
GameUI::GameUI()
{
    HPBar_back = LoadGraph("material/HPbar_02.png");
    enemyHPBar_front = LoadGraph("material/HPbar_03.png");
    enemyHPBar_name = LoadGraph("material/boss_name_01.png");
    playerHPBar_back = LoadGraph("material/player_HPBar.png");
    playerHPBar_front = LoadGraph("material/player_HPBar_green_01.png");
    playerHandle = LoadGraph("material/player_01.png");
    shadow = LoadGraph("material/shadow.png");
    gameOver_back = LoadGraph("material/lose_backGround.png");
    died_font = LoadGraph("material/died.png");
    start_font = LoadGraph("material/start_01.png");
    X_button = LoadGraph("material/X_button_01.png");
    A_button = LoadGraph("material/A_button_04.png");
}

/// <summary>
/// デストラクタ
/// </summary>
GameUI::~GameUI()
{
    DeleteGraph(HPBar_back);
    DeleteGraph(enemyHPBar_front);
    DeleteGraph(enemyHPBar_name);
    DeleteGraph(playerHPBar_back);
    DeleteGraph(playerHPBar_front);
    DeleteGraph(playerHandle);
    DeleteGraph(shadow);
    DeleteGraph(died_font);
    DeleteGraph(start_font);
    DeleteGraph(X_button);
    DeleteGraph(A_button);
    DeleteGraph(gameOver_back);
}

void GameUI::Initialize(Enemy& enemy,Player& player)
{
    oldHP_enemy = enemy.GetHP();
    drawHP_enemy = maxDrawHP_enemy;
    oldHP_player = player.GetHP();
    drawHP_player = maxDrawHP_player;
    alpha_back = 0;
    alpha_front = 0;
    alpha_bright = 0;
    alpha_UI = 0;
    alpha_Box = 0;
    shake = 0;
}

void GameUI::Update(Enemy& enemy, Player& player,bool isChange)
{
    EnemyHPUpdate(enemy);
    PlayerHPUpdate(player);

    if (isChange)
    {
        if (alpha_UI < 255)
        {
            alpha_UI += 2;
        }

        if (alpha_Box < 75)
        {
            alpha_Box += 2;
        }
    }
}

/// <summary>
/// 描画
/// </summary>
void GameUI::Draw()
{

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_Box);
    DrawBox(1405, 70, 1550, 180, GetColor(0, 0, 0), true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_UI);
    DrawExtendGraph(300 + shake, 660 + shake,1300 + shake, 720 + shake, HPBar_back, true);
    DrawExtendGraph(300 + shake, 660 + shake, drawHP_enemy + 300 + shake, 720 + shake, enemyHPBar_front, true);
    DrawExtendGraph(300, 660, 580, 700, enemyHPBar_name, true);
    DrawExtendGraph(50, 50, 850, 690, playerHPBar_back, true);
    DrawExtendGraph(163, 50, drawHP_player + 163, 690, playerHPBar_front, true);
    DrawGraph(1400, 65, A_button, true);
    DrawGraph(1400, 120, X_button, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    WhenGameOver_Draw();
    //DrawGraph(0, 0, playerHPBar_back,true);
    //DrawGraph(0, 0, playerHPBar_front, true);

    printfDx("drawHP_player:%f\n", drawHP_player);
}

void GameUI::EnemyHPUpdate(Enemy& enemy)
{
    int enemyNowHP = enemy.GetHP();

    if (oldHP_enemy > enemyNowHP)
    {
        oldHP_enemy -= 0.5f;
        drawHP_enemy = maxDrawHP_enemy * (oldHP_enemy / 100);
        // 時間に応じて揺れを計算
        double time = GetNowCount() / 1000.0; // 秒に変換
        shake = sin(time * 100) * 5; // 揺れの計算
    }
    else
    {
        shake = 0;
    }
}

void GameUI::PlayerHPUpdate(Player& player)
{
    int playerNowHP = player.GetHP();

    if (oldHP_player > playerNowHP)
    {
        float newDrawHP = (maxDrawHP_player * playerNowHP) / 4;


        if (newDrawHP < drawHP_player)
        {
            drawHP_player -= 5;

            if (drawHP_player <= 0)
            {
                drawHP_player = 0;
            }
        }
        else
        {
            oldHP_player = playerNowHP;
        }
     
    }
}

/// <summary>
/// ゲームオーバー時に描画
/// </summary>
void GameUI::WhenGameOver_Draw()
{
    if (oldHP_player <= 0)
    {
        alpha_front += 7;
        alpha_back += 3;

       /* if (alpha_back >= 255)
        {
            alpha_back = 255;
        }

        if (alpha_front >= 255)
        {
            alpha_front = 255;
        }*/

        if (alpha_front >= 500 && alpha_back >= 500)
        {
            alpha_bright += 2.5f;
        }

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_back);
        DrawGraph(0, 400, gameOver_back, true);
        DrawExtendGraph(470, 320, 1070, 620, died_font, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_bright);
        DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }
}