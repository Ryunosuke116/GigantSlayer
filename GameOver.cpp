#include "Include.h"


/// <summary>
/// インスタンス化
/// </summary>
GameOver::GameOver(SceneManager& manager) : BaseScene{ manager }
{
    if (continue_font == NULL)
    {
        continue_font = LoadGraph("material/continue_02.png");
        titleBack_font = LoadGraph("material/BackToTitle.png");
        arrow = LoadGraph("material/white_arrow_01.png");
        gameOver_font = LoadGraph("material/GAMEOVER.png");
        font_back = LoadGraph("material/lose_backGround.png");
        buttonSound = LoadSoundMem("material/SE/button.mp3");
        input = new Input();
        blackOut = new BlackOut();
    }
    select = 0;
    addAlpha_blackOut = 0;
    isAdd = false;
    isSceneChange = false;
}

/// <summary>
/// デストラクタ
/// </summary>
GameOver::~GameOver()
{
    DeleteGraph(continue_font);
    DeleteGraph(titleBack_font);
    DeleteGraph(arrow);
    DeleteGraph(gameOver_font);
    DeleteGraph(font_back);
    DeleteSoundMem(buttonSound);
    delete(input);
    delete(blackOut);
}

/// <summary>
/// 初期化
/// </summary>
void GameOver::Initialize()
{
    select = 0;
    alpha = 0;
    addAlpha_arrow = 1;
    alpha_arrow = 0;
    addAlpha = 4.5f;
    addAlpha_blackOut = 4.5f;
    blackOut->SetAlpha(255);
    isAdd = true;
    isSceneChange = false;
}

/// <summary>
/// 更新
/// </summary>
void GameOver::Update()
{
    //ゲームオーバー画面に切り替わった時明転
    if (isAdd)
    {
        blackOut->LightChangeUpdate(addAlpha);
        if (blackOut->GetAlpha() <= 0)
        {
            isAdd = false;
        }
    }

    //矢印
    if (alpha_arrow > 50)
    {
        addAlpha_arrow = -2;
    }
    else if (alpha_arrow < 0)
    {
        addAlpha_arrow = 1;
    }

    alpha_arrow += addAlpha_arrow;

    //文字
    if (alpha > 255 || alpha < 0)
    {
        addAlpha = -addAlpha;
    }
    alpha += addAlpha;

    //画面切り替え
    if (isSceneChange)
    {
        blackOut->BlackOutUpdate(addAlpha_blackOut);
        if (blackOut->GetAlpha() >= 300)
        {
            if (select == 0)
            {
                ChangeScene("Game");
            }
            if (select == 1)
            {
                ChangeScene("Title");
            }
        }
    }

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

    if (!isSceneChange)
    {
        if (input->GetNowFrameInput() & PAD_INPUT_A && !isSceneChange)
        {
            PlaySoundMem(buttonSound, DX_PLAYTYPE_BACK);
        }
        if (input->GetNowFrameInput() & PAD_INPUT_A && select == 0)
        {
            isSceneChange = true;
        }
        if (input->GetNowFrameInput() & PAD_INPUT_A && select == 1)
        {
            isSceneChange = true;
        }
    }
}

/// <summary>
/// 描画
/// </summary>
void GameOver::Draw()
{
    DrawGraph(0, 220, font_back, true);
    DrawGraph(300, 200, gameOver_font, true);

    if (select == 0)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(400, 500, continue_font, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        DrawGraph(250 - (alpha_arrow / 2), 500, arrow, true);
        DrawGraph(300, 600, titleBack_font, true);
    }
    else if (select == 1)
    {
        DrawGraph(400, 500, continue_font, true);
        DrawGraph(150 - (alpha_arrow / 2), 600, arrow, true);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(300, 600, titleBack_font, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    }

    blackOut->Draw();
}