#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include "Title.h"


/// <summary>
/// インスタンス化
/// </summary>
Title::Title(SceneManager& manager) : BaseScene{ manager } 
{
    if (camera == NULL)
    {
        camera = new Camera();
    }

    titleHandle = 0;
}

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
    titleHandle = LoadGraph("material/GigantSlayer_title.png");
    backGroundHandle = MV1LoadModel("material/skyDome/sunSet.mv1");
    camera->Initialize();
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
    camera->TitleUpdate();
}

/// <summary>
/// 描画
/// </summary>
void Title::Draw()
{
    MV1DrawModel(backGroundHandle);
    DrawGraph(100, 100, titleHandle, true);
    
    printfDx("SPACE START");
}