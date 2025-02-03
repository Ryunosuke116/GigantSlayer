#include "DxLib.h"
#include "Result.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
Result::Result(SceneManager& manager) : BaseScene{ manager } {}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Result::~Result()
{

}

/// <summary>
/// ������
/// </summary>
void Result::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void Result::Update()
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        ChangeScene("Title");
    }
}

/// <summary>
/// �`��
/// </summary>
void Result::Draw()
{
    printfDx("SPACE START");
}