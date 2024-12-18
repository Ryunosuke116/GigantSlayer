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
/// 移動可能距離
/// </summary>
/// <param name="position"></param>
void Common::MovableCalculation(VECTOR& position)
{

    float maxRange = 33.0f;

    //中心からの距離を測る
    float r = VSize(VSub(position, VGet(0, 0, 0)));

    //一定の距離に達したらそれ以上いけないようにする
    if (r >= maxRange || r <= -maxRange)
    {
        //中心座標からプレイヤー座標の距離
        VECTOR distance = VSub(VGet(0, 0, 0), position);
        //正規化
        distance = VNorm(distance);
        //戻す量を計算、加算する
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
/// プレイヤーの影を描画
/// </summary>
void Common::DrawShadow(const Map& map, const VECTOR& position)
{

    // テクスチャアドレスモードを CLAMP にする( テクスチャの端より先は端のドットが延々続く )
    SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

    // プレイヤーの直下に存在する地面のポリゴンを取得
    auto hitResultDim = MV1CollCheck_Capsule(map.GetModelHandle(), -1, position, VAdd(position, VGet(0.0f, -ShadowHeight, 0.0f)), ShadowSize);

    // 頂点データで変化が無い部分をセット
    VERTEX3D vertex[3];
    vertex[0].dif = GetColorU8(255, 255, 255, 255);
    vertex[0].spc = GetColorU8(0, 0, 0, 0);
    vertex[0].su = 0.0f;
    vertex[0].sv = 0.0f;
    vertex[1] = vertex[0];
    vertex[2] = vertex[0];

    // 球の直下に存在するポリゴンの数だけ繰り返し
    auto hitResult = hitResultDim.Dim;
    for (int i = 0; i < hitResultDim.HitNum; i++, hitResult++)
    {
        // ポリゴンの座標は地面ポリゴンの座標
        vertex[0].pos = hitResult->Position[0];
        vertex[1].pos = hitResult->Position[1];
        vertex[2].pos = hitResult->Position[2];

        // ちょっと持ち上げて重ならないようにする
        auto slideVec = VScale(hitResult->Normal, 0.5f);
        vertex[0].pos = VAdd(vertex[0].pos, slideVec);
        vertex[1].pos = VAdd(vertex[1].pos, slideVec);
        vertex[2].pos = VAdd(vertex[2].pos, slideVec);

        // ポリゴンの不透明度を設定する
        vertex[0].dif.a = 0;
        vertex[1].dif.a = 0;
        vertex[2].dif.a = 0;
        if (hitResult->Position[0].y > position.y - ShadowHeight)
            vertex[0].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(hitResult->Position[0].y - position.y) / ShadowHeight)));

        if (hitResult->Position[1].y > position.y - ShadowHeight)
            vertex[1].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(hitResult->Position[1].y - position.y) / ShadowHeight)));

        if (hitResult->Position[2].y > position.y - ShadowHeight)
            vertex[2].dif.a = static_cast<BYTE>(128 * (1.0f - static_cast<float>(fabs(hitResult->Position[2].y - position.y) / ShadowHeight)));

        // ＵＶ値は地面ポリゴンとプレイヤーの相対座標から割り出す
        vertex[0].u = (hitResult->Position[0].x - position.x) / (ShadowSize * 2.0f) + 0.5f;
        vertex[0].v = (hitResult->Position[0].z - position.z) / (ShadowSize * 2.0f) + 0.5f;
        vertex[1].u = (hitResult->Position[1].x - position.x) / (ShadowSize * 2.0f) + 0.5f;
        vertex[1].v = (hitResult->Position[1].z - position.z) / (ShadowSize * 2.0f) + 0.5f;
        vertex[2].u = (hitResult->Position[2].x - position.x) / (ShadowSize * 2.0f) + 0.5f;
        vertex[2].v = (hitResult->Position[2].z - position.z) / (ShadowSize * 2.0f) + 0.5f;

        DrawPolygon3D(vertex, 1, shadowHandle, TRUE);
    }

    // 検出した地面ポリゴン情報の後始末
    MV1CollResultPolyDimTerminate(hitResultDim);

}