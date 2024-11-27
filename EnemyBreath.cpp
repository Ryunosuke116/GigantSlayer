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

	

		const float maxTravelDistance = -34.0f;	//ブレスの最大移動距離
			
		if (Count == 0)
		{
			//座標をセット
			ResetPosition(formerPosition);
		}

		int stackCount = 0;	

		for (int i = 0; i < breathNumber; i++)
		{
			if (breaths[i].position.z <= maxTravelDistance)
			{
				breaths[i].position = VGet(formerPosition.x,
					formerPosition.y, formerPosition.z);
				//半径をリセット
				breaths[i].radius = 2;
				//方向を反転する
				//breaths[i].addPosition.x = -breaths[i].addPosition.x;
				breaths[i].isAdd = false;

				//既定の数を超えた場合、順番に消す
			//	if (Count >= attackNumber)
				//{
					breaths[i].isStop = true;
					breaths[i].effect->StopEffect();
				//}
			}
			if (!breaths[i].isStop)
			{
				breaths[i].position = VAdd(breaths[i].position, breaths[i].addPosition);
				breaths[i].radius += 0.1f;
				//エフェクト
				breaths[i].effectPosition = VGet(breaths[i].position.x, breaths[i].position.y,
					breaths[i].position.z);

				breaths[i].effect->StopEffect();
				breaths[i].effect->PlayEffect();
				breaths[i].effect->PositionUpdate(breaths[i].effectPosition);
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
	//if (Count >= attackNumber + (attackNumber / 2))
	if (Count >= breathNumber + (breathNumber / 2))
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

	addPosition.z = -addPosition_Z;
	addPosition.x = addPosition_X;

	if (addPosition_X <= -0.5f)
	{
		isDirection = false;
		isStopAdd = true;
	}
	else if (addPosition_X >= 0.5f)
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

void EnemyBreath::Rotation(VECTOR playerPos,VECTOR enemyPos)
{

	rotation = VSub(playerPos, enemyPos);
	rotation = VNorm(rotation);

	for (int i = 0; i < breathNumber; i++)
	{
		breaths[i].addPosition.x += rotation.x;
	}
}