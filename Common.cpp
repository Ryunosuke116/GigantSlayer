#include "Common.h"

Common::Common()
{
    shadowHandle = LoadGraph("material/Shadow.tga");
}

void Common::Update(Player& player, std::array<Object*, 4> objects)
{
    VECTOR playerPosition = player.GetPosition();
    MovableCalculation(playerPosition);
    player.SetPosition(playerPosition);

    for (auto& object : objects)
    {
        VECTOR objectPosition = object->GetPosition();
        MovableCalculation(objectPosition);
        object->SetPosition(objectPosition);
    }
}

/// <summary>
/// �ړ��\����
/// </summary>
/// <param name="position"></param>
void Common::MovableCalculation(VECTOR& position)
{

    float maxRange = 33.0f;

    //���S����̋����𑪂�
    float r = VSize(VSub(position, VGet(0, 0, 0)));

    //���̋����ɒB�����炻��ȏア���Ȃ��悤�ɂ���
    if (r >= maxRange || r <= -maxRange)
    {
        //���S���W����v���C���[���W�̋���
        VECTOR distance = VSub(VGet(0, 0, 0), position);
        //���K��
        distance = VNorm(distance);
        //�߂��ʂ��v�Z�A���Z����
        VECTOR returnPosition = VScale(distance, (r - maxRange));
        position = VAdd(position, returnPosition);
    }
}



void Common::Draw(Map& map, const VECTOR& PlayerPosition, const Enemy& enemy)
{
    DrawShadow(map, PlayerPosition);
    DrawShadow(map, enemy.bullet->GetPosition());
    DrawShadow(map, enemy.GetBottomPosition());
}

/// <summary>
/// �v���C���[�̉e��`��
/// </summary>
void Common::DrawShadow(const Map& map, const VECTOR& position)
{

    // �e�N�X�`���A�h���X���[�h�� CLAMP �ɂ���( �e�N�X�`���̒[����͒[�̃h�b�g�����X���� )
    SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

    // �v���C���[�̒����ɑ��݂���n�ʂ̃|���S�����擾
    auto hitResultDim = MV1CollCheck_Capsule(map.GetModelHandle(), -1, position, VAdd(position, VGet(0.0f, -ShadowHeight, 0.0f)), ShadowSize);

    // ���_�f�[�^�ŕω��������������Z�b�g
    VERTEX3D vertex[3];
    vertex[0].dif = GetColorU8(255, 255, 255, 255);
    vertex[0].spc = GetColorU8(0, 0, 0, 0);
    vertex[0].su = 0.0f;
    vertex[0].sv = 0.0f;
    vertex[1] = vertex[0];
    vertex[2] = vertex[0];

    // ���̒����ɑ��݂���|���S���̐������J��Ԃ�
    auto hitResult = hitResultDim.Dim;
    for (int i = 0; i < hitResultDim.HitNum; i++, hitResult++)
    {
        // �|���S���̍��W�͒n�ʃ|���S���̍��W
        vertex[0].pos = hitResult->Position[0];
        vertex[1].pos = hitResult->Position[1];
        vertex[2].pos = hitResult->Position[2];

        // ������Ǝ����グ�ďd�Ȃ�Ȃ��悤�ɂ���
        auto slideVec = VScale(hitResult->Normal, 0.5f);
        vertex[0].pos = VAdd(vertex[0].pos, slideVec);
        vertex[1].pos = VAdd(vertex[1].pos, slideVec);
        vertex[2].pos = VAdd(vertex[2].pos, slideVec);

        // �|���S���̕s�����x��ݒ肷��
        vertex[0].dif.a = 0;
        vertex[1].dif.a = 0;
        vertex[2].dif.a = 0;
        if (hitResult->Position[0].y > position.y - ShadowHeight)
            vertex[0].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(hitResult->Position[0].y - position.y) / ShadowHeight)));

        if (hitResult->Position[1].y > position.y - ShadowHeight)
            vertex[1].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(hitResult->Position[1].y - position.y) / ShadowHeight)));

        if (hitResult->Position[2].y > position.y - ShadowHeight)
            vertex[2].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(hitResult->Position[2].y - position.y) / ShadowHeight)));

        // �t�u�l�͒n�ʃ|���S���ƃv���C���[�̑��΍��W���犄��o��
        vertex[0].u = (hitResult->Position[0].x - position.x) / (ShadowSize * 2.0f) + 0.5f;
        vertex[0].v = (hitResult->Position[0].z - position.z) / (ShadowSize * 2.0f) + 0.5f;
        vertex[1].u = (hitResult->Position[1].x - position.x) / (ShadowSize * 2.0f) + 0.5f;
        vertex[1].v = (hitResult->Position[1].z - position.z) / (ShadowSize * 2.0f) + 0.5f;
        vertex[2].u = (hitResult->Position[2].x - position.x) / (ShadowSize * 2.0f) + 0.5f;
        vertex[2].v = (hitResult->Position[2].z - position.z) / (ShadowSize * 2.0f) + 0.5f;

        DrawPolygon3D(vertex, 1, shadowHandle, TRUE);
    }

    // ���o�����n�ʃ|���S�����̌�n��
    MV1CollResultPolyDimTerminate(hitResultDim);

}