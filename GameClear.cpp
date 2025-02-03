#include "Include.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
GameClear::GameClear(SceneManager& manager) : BaseScene{ manager } 
{
    if (input == NULL)
    {
        font_back = LoadGraph("material/lose_backGround.png");
        clear_font = LoadGraph("material/GAMECLEAR_01.png");
        titleBack_font = LoadGraph("material/ResetTitle_01.png");
        input = new Input();
    }
    alpha = 0;
    addAlpha = 0;
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
    alpha = 0;
    addAlpha = 4.5f;
}

/// <summary>
/// �X�V
/// </summary>
void GameClear::Update()
{
    input->Update();

    if (alpha > 255 || alpha < 0)
    {
        addAlpha = -addAlpha;
    }
    alpha += addAlpha;

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

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawGraph(290, 600, titleBack_font, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}