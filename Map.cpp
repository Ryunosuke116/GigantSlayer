#include "Include.h"

/// <summary>
/// インスタンス化
/// </summary>
Map::Map()
{
    backGroundHandle = -1;
    fieldHandle = -1;
    time = 0;
    position = VGet(0, 0, 0);
    effectPosition = VGet(0, 0, 200);
    fieldPosition = VGet(0, 0, 0);
    rotationPosition = VGet(0, 0, 0);
    effect = new Effect();
}

/// <summary>
/// 
/// </summary>
Map::~Map()
{
    MV1DeleteModel(backGroundHandle);
    MV1DeleteModel(fieldHandle);
}

/// <summary>
/// 初期化
/// </summary>
void Map::Initialize()
{
    fieldPosition = VGet(0, -1, 0);
    rotationPosition = VGet(0, 3.2f, 0);
    time = 0;
    // スカイドームのポジション設定
    backGroundHandle = MV1LoadModel("material/skyDome/sunSet.mv1");
    fieldHandle = MV1LoadModel("material/uploads_files_2988017_round+table.mv1");
    effect->Initialize("material/TouhouStrategy/Red_Background.efkefc", 3.0f, effectPosition);
    MV1SetPosition(backGroundHandle, position);
    MV1SetPosition(fieldHandle, fieldPosition);

    //モデルの大きさ調整
    MV1SetScale(fieldHandle, VGet(0.17f, 0.17f, 0.17f));

}

void Map::Update()
{
    // 定期的にエフェクトを再生する
    if (time % 1200 == 0)
    {
        effect->StopEffect();
        effect->PlayEffect();

        effect->SetRotation(rotationPosition);
        effect->PositionUpdate(effectPosition);
    }
   

    //effect->SetRotation(scalePosition);

    //時間を経過させる
    time++;
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{

    //3d描画
    MV1DrawModel(backGroundHandle);
    MV1DrawModel(fieldHandle);
    printfDx("rotation.y %f", rotationPosition.y);

}