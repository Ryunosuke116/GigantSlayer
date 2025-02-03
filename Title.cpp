#include "Include.h"


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
        start_font = LoadGraph("material/start_04.png");
        movieHandle = LoadGraph("material/mp4/title_movie.mpg");
        font_back = LoadGraph("material/lose_backGround.png");
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
    PlayMovieToGraph(movieHandle);
    camera->Initialize();
    blackOut->Initialize();
    alpha = 0;
    addAlpha = 2;
    alpha_bright = 0;
    isPush = false;
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
    //再生終了したら最初から流す
    if (GetMovieStateToGraph(movieHandle) == 0)
    {
        SeekMovieToGraph(movieHandle, 0);
        PlayMovieToGraph(movieHandle);
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
    DrawExtendGraph(0,0,1600,900,movieHandle,false);
    DrawGraph(400, 100, titleHandle, true);

    DrawExtendGraph(0, 570,1600,670, font_back, true);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawGraph(300, 550, start_font, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
   // PlayMovie("material/mp4/a.avi", 1, DX_MOVIEPLAYTYPE_NORMAL);
    blackOut->Draw();
    
}