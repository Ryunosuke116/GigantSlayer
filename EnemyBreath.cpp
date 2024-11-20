#include"EffekseerForDXLib.h"
#include <vector>
#include <cmath>
#include "Effect.h"
#include "Enemy.h"
#include"object.h"
#include "EnemyBreath.h"

/// <summary>
/// インスタンス化
/// </summary>
EnemyBreath::EnemyBreath()
{
	formerPosition = VGet(0, 0, 0);
	effectPosition = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	addPosition_X = 0;
	addPosition_Z = 0;
	addRotation_Y = 0;
	effectPlayStack = 0;
	radius = 0;
	Count = 0;
	attackNumber = 0;
	fixCount = 0;
	attackStack = 1;
	isStopAdd = false;
	isDirection = false;
}

/// <summary>
/// 
/// </summary>
EnemyBreath::~EnemyBreath()
{

}

/// <summary>
/// 初期化
/// </summary>
void EnemyBreath::Initialize()
{
	effectPosition = VGet(formerPosition.x, formerPosition.y, formerPosition.z - 30.0f);
	rotation = VGet(0, 20.5f, 0);
	addPosition_X = 0;
	addPosition_Z = 2.0f;
	addRotation_Y = 0.0175f;
	fixCount = 3;
	int breathNumber = 42;	//当たり判定の数
	isDirection = false;
	attackNumber += breathNumber * 2;
	//effect = new Effect();
	//effect->Initialize("material/TouhouStrategy/fire.efkefc", 10.0f, effectPosition);

	

	for (int i = 0; i < breathNumber; i++)
	{
		Breath breath;
		breath.isAdd = false;
		breath.isStop = false;
		breath.addPosition = VGet(0, 0, 0);
		breath.position = VGet(formerPosition.x, formerPosition.y, formerPosition.z);
		breath.effectPosition = VGet(formerPosition.x, formerPosition.y - 10, formerPosition.z);
		breath.radius = 2;

		Direction(breath.addPosition);
		auto effect = new Effect;
	
		effect->Initialize("material/TouhouStrategy/utsuho_sun_area1.efkefc", 1.0f, breath.effectPosition);

		breath.effect = effect;
		effect->SetPosition(breath.effectPosition);

		breaths.push_back(breath);
	}

	radius = 3;
}

/// <summary>
/// 更新
/// </summary>
void EnemyBreath::Update()
{
	if (isAttack)
	{
		isEffect = true;

		////エフェクトを再生
		//if (isEffect)
		//{
		//	//発動してから60fの間再生
		//	if (effectPlayStack <= 120)
		//	{
		//		effectPlayStack++;
		//		rotation.y += addRotation_Y;
		//		if (rotation.y >= 21.0f || rotation.y <= 20.0f)
		//		{
		//			addRotation_Y *= -1;
		//		}
		//		effect->SetRotation(rotation);
		//		//エフェクトを再生
		//		effect->PositionUpdate(effectPosition);
		//	}
		//	else
		//	{
		//		//エフェクトを停止
		//		effect->StopEffect();
		//		effectPosition = VGet(formerPosition.x, formerPosition.y, formerPosition.z - 30);
		//		effectPlayStack = 0;
		//		isEffect = false;
		//	}
		//}

		const float maxTravelDistance = -34.0f;	//ブレスの最大移動距離
			
		if (Count == 0)
		{
			//座標をセット
			ResetPosition(formerPosition);
		}

		int stackCount = 0;	

		for (auto& breath : breaths)
		{
			if (breath.position.z <= maxTravelDistance)
			{
				breath.position = VGet(formerPosition.x,
					formerPosition.y, formerPosition.z);
				//半径をリセット
				breath.radius = 2;
				//方向を反転する
				breath.addPosition.x = -breath.addPosition.x;
				breath.isAdd = false;

				//既定の数を超えた場合、順番に消す
				if (Count >= attackNumber)
				{
					breath.isStop = true;
				}

	
			}
			if (!breath.isStop)
			{
				breath.position = VSub(breath.position, breath.addPosition);
				breath.radius += 0.1f;
				//エフェクト
				breath.effectPosition = VGet(breath.position.x, breath.position.y,
					breath.position.z);

				breath.effect->StopEffect();
				breath.effect->PlayEffect();
				breath.effect->PositionUpdate(breath.effectPosition);
			}
			stackCount++;

			// 球を一つずつ出す
			if (attackStack <= stackCount)
			{
				break;
			}
		}

		attackStack++;
		Count++;
		
	}
	
	//カウントに達した場合、攻撃終了
	if (Count >= attackNumber + (attackNumber / 2))
	{
		addPosition_X = 0;
		isStopAdd = false;
		isDirection = false;
		isAttack = false;
		isEffect = false;
		Count = 0;
		attackStack = 0;
		//座標をセット
		ResetPosition(formerPosition);
		
		for (auto& breath : breaths)
		{
			breath.radius = 2;
			Direction(breath.addPosition);
			breath.isStop = false;
			breath.effect->StopEffect();
		}
	}

}

/// <summary>
/// 描画
/// </summary>
void EnemyBreath::Draw()
{
	for (const auto& breath : breaths)
	{
		//DrawSphere3D(breath.position, breath.radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
	}

}

/// <summary>
/// 座標の保存
/// </summary>
/// <param name="position"></param>
void EnemyBreath::SetPosition(const VECTOR position)
{
	formerPosition = VGet(position.x, position.y, position.z - 10.0f);
}

/// <summary>
/// 座標をリセット
/// </summary>
/// <param name="position"></param>
void EnemyBreath::ResetPosition(const VECTOR position)
{
	for (auto& breath : breaths)
	{
		breath.position = VGet(position.x, position.y, position.z);
	}
}

/// <summary>
///	方向を反転する
/// </summary>
/// <param name="addPosition"></param>
void EnemyBreath::Direction(VECTOR& addPosition)
{

	addPosition.z = addPosition_Z;
	addPosition.x = addPosition_X;

	if (addPosition_X <= -0.4f)
	{
		isDirection = false;
		isStopAdd = true;
	}
	else if (addPosition_X >= 0.4f)
	{
		isDirection = true;
		isStopAdd = true;
	}

	if (fixCount >= 3)
	{
		isStopAdd = false;
		fixCount = 0;
	}

	if (!isDirection)
	{
		if (!isStopAdd)
		{
			addPosition_X += 0.02f;
		}
		else
		{
			fixCount++;
		}
	}
	else
	{
		if (!isStopAdd)
		{
			addPosition_X -= 0.02f;
		}
		else
		{
			fixCount++;
		}
	}
}