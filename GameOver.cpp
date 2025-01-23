#include "GameOver.h"
#include <iostream>
#include <array>

/// <summary>
/// インスタンス化
/// </summary>
GameOver::GameOver(SceneManager& manager) : BaseScene{ manager }
{
    if (continue_font == NULL)
    {
        continue_font = LoadGraph("material/continue_02.png");
        titleBack_font = LoadGraph("material/BackToTitle.png");
        input = new Input();
    }
    select = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
GameOver::~GameOver()
{

}

/// <summary>
/// 初期化
/// </summary>
void GameOver::Initialize()
{
    select = 0;
}

/// <summary>
/// 更新
/// </summary>
void GameOver::Update()
{
    input->Update();

    if (input->GetNowFrameInput() & PAD_INPUT_UP)
    {
        select--;
    }
    if (input->GetNowFrameInput() & PAD_INPUT_DOWN)
    {
        select++;
    }

    if (select < 0)
    {
        select = 0;
    }
    if (select > 1)
    {
        select = 1;
    }

    if (input->GetNowFrameInput() & PAD_INPUT_A && select == 0)
    {
        ChangeScene("Game");
    }
    if (input->GetNowFrameInput() & PAD_INPUT_A && select == 1)
    {
        ChangeScene("Title");
    }
}

/// <summary>
/// 描画
/// </summary>
void GameOver::Draw()
{
    DrawGraph(400, 500, continue_font, true);
    DrawGraph(300, 600, titleBack_font, true);
}