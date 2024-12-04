#include "DxLib.h"
#include "Result.h"

/// <summary>
/// インスタンス化
/// </summary>
Result::Result(SceneManager& manager) : BaseScene{ manager } {}

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
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        ChangeScene("Title");
    }
}

/// <summary>
/// 描画
/// </summary>
void Result::Draw()
{
    printfDx("SPACE START");
}