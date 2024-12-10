#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include "Title.h"


/// <summary>
/// �C���X�^���X��
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
/// �f�X�g���N�^
/// </summary>
Title::~Title()
{

}

/// <summary>
/// ������
/// </summary>
void Title::Initialize()
{
    titleHandle = LoadGraph("material/GigantSlayer_title.png");
    backGroundHandle = MV1LoadModel("material/skyDome/sunSet.mv1");
    camera->Initialize();
}

/// <summary>
/// �X�V
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
/// �`��
/// </summary>
void Title::Draw()
{
    MV1DrawModel(backGroundHandle);
    DrawGraph(100, 100, titleHandle, true);
    
    printfDx("SPACE START");
}