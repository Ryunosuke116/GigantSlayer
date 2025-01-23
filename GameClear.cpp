#include "DxLib.h"
#include "GameClear.h"

/// <summary>
/// インスタンス化
/// </summary>
GameClear::GameClear(SceneManager& manager) : BaseScene{ manager } 
{
    if (input == NULL)
    {
        font_back = LoadGraph("material/lose_backGround.png");
        clear_font = LoadGraph("material/GAMECLEAR_01.png");
        titleBack_font = LoadGraph("material/ResetTitle.png");
        input = new Input();
    }
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
    
}

/// <summary>
/// 更新
/// </summary>
void GameClear::Update()
{
    input->Update();

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
    DrawGraph(300, 600, titleBack_font, true);
}