#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include "Title.h"


/// <summary>
/// インスタンス化
/// </summary>
Title::Title(SceneManager& manager) : BaseScene{ manager } {}

/// <summary>
/// デストラクタ
/// </summary>
Title::~Title()
{

}

/// <summary>
/// 初期化
/// </summary>
void Title::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void Title::Update()
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        ChangeScene("Game");
    }
}

/// <summary>
/// 描画
/// </summary>
void Title::Draw()
{
    printfDx("SPACE START");
}