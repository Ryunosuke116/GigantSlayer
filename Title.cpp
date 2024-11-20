#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include "Title.h"


/// <summary>
/// �C���X�^���X��
/// </summary>
Title::Title(SceneManager& manager) : BaseScene{ manager } {}

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
}

/// <summary>
/// �`��
/// </summary>
void Title::Draw()
{
    printfDx("SPACE START");
}