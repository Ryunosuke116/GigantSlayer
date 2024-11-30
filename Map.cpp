#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Map.h"

/// <summary>
/// インスタンス化
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
/// 初期化
/// </summary>
void Map::Initialize()
{
    fieldPosition = VGet(0, -1, 0);

    // スカイドームのポジション設定
    backGroundHandle = MV1LoadModel("material/skyDome/sunSet.mv1");
    fieldHandle = MV1LoadModel("material/uploads_files_2988017_round+table.mv1");
    effect->Initialize("material/TouhouStrategy/Background.efkefc", 1.2f, effectPosition);
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
        effect->SetRotation(VGet(0, 10, 0));
    }

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
 

}