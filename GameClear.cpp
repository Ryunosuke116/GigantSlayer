#include "DxLib.h"
#include "GameClear.h"

/// <summary>
/// �C���X�^���X��
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
/// �f�X�g���N�^
/// </summary>
GameClear::~GameClear()
{

}

/// <summary>
/// ������
/// </summary>
void GameClear::Initialize()
{
    
}

/// <summary>
/// �X�V
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
/// �`��
/// </summary>
void GameClear::Draw()
{
    DrawGraph(0, 400, font_back, true);
    DrawGraph(200, 380, clear_font, true);
    DrawGraph(300, 600, titleBack_font, true);
}