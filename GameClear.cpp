#include "Include.h"

/// <summary>
/// インスタンス化
/// </summary>
GameClear::GameClear(SceneManager& manager) : BaseScene{ manager } 
{
    if (input == NULL)
    {
        font_back = LoadGraph("material/lose_backGround.png");
        clear_font = LoadGraph("material/GAMECLEAR_01.png");
        titleBack_font = LoadGraph("material/ResetTitle_01.png");
        input = new Input();
    }
    alpha = 0;
    addAlpha = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
GameClear::~GameClear()
{

}

/// <summary>
/// 初期化
/// </summary>
void GameClear::Initialize()
{
    alpha = 0;
    addAlpha = 4.5f;
}

/// <summary>
/// 更新
/// </summary>
void GameClear::Update()
{
    input->Update();

    if (alpha > 255 || alpha < 0)
    {
        addAlpha = -addAlpha;
    }
    alpha += addAlpha;

    if (input->GetNowFrameInput() & PAD_INPUT_A || 
        CheckHitKey(KEY_INPUT_SPACE))
    {
        ChangeScene("Title");
    }
}

/// <summary>
/// 描画
/// </summary>
void GameClear::Draw()
{
    DrawGraph(0, 400, font_back, true);
    DrawGraph(200, 380, clear_font, true);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawGraph(290, 600, titleBack_font, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}