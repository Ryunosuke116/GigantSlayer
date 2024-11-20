#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include <cmath>
#include "Effect.h"
#include "EnemyCircleAttack.h"

/// <summary>
/// インスタンス化
/// </summary>
EnemyCircleAttack::EnemyCircleAttack()
{
	bulletPosition = VGet(0, 0, 0);
	addPosition_X = 0;
	addPosition_Z = 0;
	radius = 0;
	stack = 0;
	Count = 0;
	attackStack = 1;
	is = false;
	isAttack = false;
	isSetPosition = false;
}

/// <summary>
/// 
/// </summary>
EnemyCircleAttack::~EnemyCircleAttack()
{

}

/// <summary>
/// 初期化
/// </summary>
void EnemyCircleAttack::Initialize()
{
	int circleAttackNum = 36;

	for (int i = 0; i < circleAttackNum; i++)
	{
		auto effect = new Effect;
		circleAttack.addPosition = VGet(0, 0, 0);
		circleAttack.position = VGet(bulletPosition.x, bulletPosition.y, bulletPosition.z);
		circleAttack.effectPosition = VGet(bulletPosition.x, bulletPosition.y - 10, bulletPosition.z);

		CircumferenceCalculation(circleAttack.addPosition.x, circleAttack.addPosition.z);
		effect->Initialize("material/TouhouStrategy/utsuho_sun_area1.efkefc", 1.0f, circleAttack.effectPosition);
		
		circleAttack.effect = effect;
		effect->SetPosition(circleAttack.effectPosition);
		stack += 5;
		circleAttacks.push_back(circleAttack);
		
	}
	
	radius = 2;
	
}

/// <summary>
/// 更新
/// </summary>
void EnemyCircleAttack::Update()
{
	if (isAttack)
	{
		if (Count == 0)
		{
			//座標をセット
			ResetPosition(bulletPosition);
		}

		//　円状の攻撃をする
		for (auto& CircleAttack : circleAttacks)
		{
			CircleAttack.position = VSub(CircleAttack.position, CircleAttack.addPosition);
			//エフェクト
			CircleAttack.effectPosition = VGet(CircleAttack.position.x, CircleAttack.position.y, 
				CircleAttack.position.z);

			CircleAttack.effect->StopEffect();
			CircleAttack.effect->PlayEffect();
			CircleAttack.effect->PositionUpdate(CircleAttack.effectPosition);
		}
		Count++;

	}


	int maxCount = 80;
	//max値になった場合、リセットする
	if (Count > maxCount)
	{
		isAttack = false;
		Count = 0;
		attackStack = 0;
		//座標をセット
		ResetPosition(enemyPosition);
		for (auto& CircleAttack : circleAttacks)
		{
			CircleAttack.effect->StopEffect();
		}
	}
	
}

/// <summary>
/// 描画
/// </summary>
void EnemyCircleAttack::Draw()
{
	if (isAttack)
	{
		for (const auto& CircleAttack : circleAttacks)
		{
		//	DrawSphere3D(CircleAttack.position, radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
			//CircleAttack.effect->Draw();
		}
	}
		
	
}

/// <summary>
/// 円周計算
/// </summary>
/// <param name="x"></param>
/// <param name="z"></param>
void EnemyCircleAttack::CircumferenceCalculation(float& x,float& z)
{
	float circleRadio = 3.14f;

	x = (2 * circleRadio) * stack / 360;
	z = (2 * circleRadio) * stack / 360;
	x = 0 + 1 * cos(x);
	z = 0 + 1 * sin(z);

	x *= speed;
	z *= speed;

}

/// <summary>
/// 座標の保存
/// </summary>
/// <param name="position"></param>
void EnemyCircleAttack::SetPosition(const VECTOR position)
{
	bulletPosition = VGet(position.x, position.y, position.z);
}

/// <summary>
/// 座標をリセット
/// </summary>
/// <param name="position"></param>
void EnemyCircleAttack::ResetPosition(const VECTOR position)
{
	for (auto& CircleAttack : circleAttacks)
	{
		CircleAttack.position = VGet(position.x, position.y + 3, position.z);
	}
}

