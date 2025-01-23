#include "DxLib.h"
#include "Result.h"

/// <summary>
/// インスタンス化
/// </summary>
Result::Result(SceneManager& manager) : BaseScene{ manager } 
{
    if (input == NULL)
    {
        font_back = LoadGraph("material/lose_backGround.png");
        clear_font = LoadGraph("material/GAMECLEAR_01.png");
        input = new Input();
    }
}

/// <summary>
/// デストラクタ
/// </summary>
Result::~Result()
{

}

/// <summary>
/// 初期化
/// </summary>
void Result::Initialize()
{
    
}

/// <summary>
/// 更新
/// </summary>
void Result::Update()
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
void Result::Draw()
{
    DrawGraph(0, 400, font_back, true);
    DrawGraph(200, 380, clear_font, true);
}