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
        input = new Input();
        blackOut = new BlackOut();
    }

    titleHandle = 0;

    start_font = LoadGraph("material/start_03.png");
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
    blackOut->Initialize();
    alpha = 0;
    addAlpha = 2;
    alpha_bright = 0;
}

/// <summary>
/// 更新
/// </summary>
void Title::Update()
{
    camera->TitleUpdate();
    input->Update();

    alpha += addAlpha;

    if (alpha <= 0 || alpha >= 255)
    {
        addAlpha = -addAlpha;
    }

    if (input->GetNowFrameInput() & PAD_INPUT_A ||
        CheckHitKey(KEY_INPUT_SPACE))
    {
        isPush = true;

    }

    if (isPush)
    {
        blackOut->BlackOutUpdate(4.5f);
        if (blackOut->GetAlpha() >= 300)
        {
            ChangeScene("Game");
        }
    }

}

/// <summary>
/// 描画
/// </summary>
void Title::Draw()
{
    MV1DrawModel(backGroundHandle);
    DrawGraph(100, 100, titleHandle, true);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawGraph(300, 550, start_font, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    blackOut->Draw();
    
}