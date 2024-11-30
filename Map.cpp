#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Map.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
Map::Map()
{
    backGroundHandle = -1;
    fieldHandle = -1;
    time = 0;
    position = VGet(0, 0, 0);
    effectPosition = VGet(0, 0, 50);
    fieldPosition = VGet(0, 0, 0);
    effect = new Effect();
}

/// <summary>
/// 
/// </summary>
Map::~Map()
{

}

/// <summary>
/// ������
/// </summary>
void Map::Initialize()
{
    fieldPosition = VGet(0, -1, 0);

    // �X�J�C�h�[���̃|�W�V�����ݒ�
    backGroundHandle = MV1LoadModel("material/skyDome/sunSet.mv1");
    fieldHandle = MV1LoadModel("material/uploads_files_2988017_round+table.mv1");
    effect->Initialize("material/TouhouStrategy/Background.efkefc", 1.2f, effectPosition);
    MV1SetPosition(backGroundHandle, position);
    MV1SetPosition(fieldHandle, fieldPosition);

    //���f���̑傫������
    MV1SetScale(fieldHandle, VGet(0.17f, 0.17f, 0.17f));

}

void Map::Update()
{
    // ����I�ɃG�t�F�N�g���Đ�����
    if (time % 1200 == 0)
    {
        effect->StopEffect();
        effect->PlayEffect();
        effect->SetRotation(VGet(0, 10, 0));
    }

    //���Ԃ��o�߂�����
    time++;
}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
    //3d�`��
    MV1DrawModel(backGroundHandle);
    MV1DrawModel(fieldHandle);
 

}