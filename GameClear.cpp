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
        buttonSound = LoadSoundMem("material/SE/button.mp3");
        input = new Input();
        blackOut = new BlackOut();
    }
    alpha = 0;
    addAlpha = 0;
    alpha_white = 0;
    alpha_black = 0;
    addAlpha_black = 0;
    addAlpha_white = 0;
    isAdd = false;
}

/// <summary>
/// デストラクタ
/// </summary>
GameClear::~GameClear()
{
    delete(input);
    delete(blackOut);
    DeleteGraph(font_back);
    DeleteGraph(clear_font);
    DeleteGraph(titleBack_font);
    DeleteSoundMem(buttonSound);
}

/// <summary>
/// 初期化
/// </summary>
void GameClear::Initialize()
{
    alpha = 0;
    addAlpha = 4.5f;
    alpha_white = 255;
    alpha_black = 0;
    addAlpha_black = 4.5f;
    addAlpha_white = 4.5f;
    blackOut->SetAlpha(0);
    isAdd = false;
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

    if (alpha_white > 0)
    {
        alpha_white -= addAlpha_white;
    }

    if (isAdd)
    {
        alpha_black += addAlpha_black;
        if (alpha_black >= 350)
        {
            ChangeScene("Title");
        }
    }

    if ((input->GetNowFrameInput() & PAD_INPUT_A || 
        CheckHitKey(KEY_INPUT_SPACE)) && !isAdd)
    {
        isAdd = true;
        PlaySoundMem(buttonSound, DX_PLAYTYPE_BACK);
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

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_white);
    DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_black);
    DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}