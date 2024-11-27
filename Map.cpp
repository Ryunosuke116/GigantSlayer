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
    position = VGet(0, 0, 0);
    fieldPosition = VGet(0, 0, 0);
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
    MV1SetPosition(backGroundHandle, position);
    MV1SetPosition(fieldHandle, fieldPosition);

    //モデルの大きさ調整
    MV1SetScale(fieldHandle, VGet(0.17f, 0.17f, 0.17f));

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