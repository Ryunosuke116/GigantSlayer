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
    alpha = 0;
    addAlpha = 4.5f;
}

/// <summary>
/// 更新
/// </summary>
void GameOver::Update()
{
    if (alpha > 255 || alpha < 0)
    {
        addAlpha = -addAlpha;
    }
    alpha += addAlpha;

    input->Update();

    if (input->GetNowFrameInput() & PAD_INPUT_UP && select != 0)
    {
        select--;
        alpha = 0;
        addAlpha = 4.5f;
    }
    if (input->GetNowFrameInput() & PAD_INPUT_DOWN && select != 1)
    {
        select++;
        alpha = 0;
        addAlpha = 4.5f;
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
    if (select == 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(400, 500, continue_font, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawGraph(300, 600, titleBack_font, true);
    }
    else if (select == 1)
    {
        DrawGraph(400, 500, continue_font, true);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(300, 600, titleBack_font, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }
}