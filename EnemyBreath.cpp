#include"EffekseerForDXLib.h"
#include <vector>
#include <cmath>
#include "Effect.h"
#include "Enemy.h"
#include "object.h"
#include "EnemyCalculation.h"
#include "EnemyBreath.h"

/// <summary>
/// �C���X�^���X��
/// </summary>
EnemyBreath::EnemyBreath()
{
	formerPosition = VGet(0, 0, 0);
	effectPosition = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	addPosition_X = 0;
	addPosition_Z = 0;
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
/// ������
/// </summary>
void EnemyBreath::Initialize()
{
	effectPosition = VGet(formerPosition.x, formerPosition.y, formerPosition.z - 30.0f);
	rotation = VGet(0, 20.5f, 0);
	addPosition_X = 0;
	addPosition_Z = 2.0f;

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

		auto effect = new Effect;
	
		effect->Initialize("material/TouhouStrategy/utsuho_sun_area1.efkefc", 1.0f, breath.effectPosition);

		breath.effect = effect;
		effect->SetPosition(breath.effectPosition);

		breaths.push_back(breath);
	}


	radius = 3;
}

/// <summary>
/// �X�V
/// </summary>
void EnemyBreath::Update()
{
	if (isAttack)
	{
		isEffect = true;

		const float maxTravelDistance = -34.0f;	//�u���X�̍ő�ړ�����
			
		if (Count == 0)
		{
			//���W���Z�b�g
			ResetPosition(formerPosition);
		}

		int stackCount = 0;	

		for (int i = 0; i < breathNumber; i++)
		{
			if (breaths[i].position.z <= maxTravelDistance)
			{
				breaths[i].position = VGet(formerPosition.x,
					formerPosition.y, formerPosition.z);
				//���a�����Z�b�g
				breaths[i].radius = 2;
				//�����𔽓]����
				//breaths[i].addPosition.x = -breaths[i].addPosition.x;
				breaths[i].isAdd = false;

				//���Ԃɏ���
				breaths[i].isStop = true;
				breaths[i].effect->StopEffect();
			}
			if (!breaths[i].isStop)
			{
				breaths[i].position = VAdd(breaths[i].position, breaths[i].addPosition);
				breaths[i].radius += 0.1f;
				//�G�t�F�N�g
				breaths[i].effectPosition = VGet(breaths[i].position.x, breaths[i].position.y,
					breaths[i].position.z);

				breaths[i].effect->StopEffect();
				breaths[i].effect->PlayEffect();
				breaths[i].effect->PositionUpdate(breaths[i].effectPosition);
			}
			stackCount++;

			// ��������o��
			if (attackStack <= stackCount)
			{
				break;
			}
		}

		attackStack++;
		Count++;
		
	}
	
	//�J�E���g�ɒB�����ꍇ�A�U���I��
	if (Count >= breathNumber + (breathNumber / 2))
	{
		addPosition_X = 0;
		isStopAdd = false;
		isDirection = false;
		isAttack = false;
		isEffect = false;
		Count = 0;
		attackStack = 0;
		//���W���Z�b�g
		ResetPosition(formerPosition);
		
		for (auto& breath : breaths)
		{
			breath.radius = 2;
			breath.isStop = false;
			breath.effect->StopEffect();
		}
	}

}

/// <summary>
/// �`��
/// </summary>
void EnemyBreath::Draw()
{
	for (const auto& breath : breaths)
	{
		//DrawSphere3D(breath.position, breath.radius, 16, GetColor(0, 0, 0), GetColor(255, 255, 255), false);
	}

}

/// <summary>
/// ���W�̕ۑ�
/// </summary>
/// <param name="position"></param>
void EnemyBreath::SetPosition(const VECTOR position)
{
	formerPosition = VGet(position.x, position.y, position.z - 10.0f);
}

/// <summary>
/// ���W�����Z�b�g
/// </summary>
/// <param name="position"></param>
void EnemyBreath::ResetPosition(const VECTOR position)
{
	for (auto& breath : breaths)
	{
		breath.position = VGet(position.x, position.y, position.z);
	}
}



void EnemyBreath::Rotation(VECTOR playerPos,VECTOR enemyPos)
{
	//�G���U�����[�V�����ɓ���O�ɕ����x�N�g�������߂�
	rotation = VSub(playerPos, enemyPos);
	rotation.y = 0;
	rotation = VNorm(rotation);

	float angle = atan2(rotation.z, rotation.x);
	float angleDegree = angle * 180 / DX_PI_F;
	float maxDeg = angleDegree + 30.0f;
	float minDeg = angleDegree - 30.0f;

	for (auto& breath : breaths)
	{
		EnemyCalculation::CircumferenceCalculation(breath.addPosition, rotation.x, rotation.z, angleDegree, speed);
		
		if (angleDegree <= minDeg)
		{
			isDirection = false;
			isStopAdd = true;
		}
		else if (angleDegree >= maxDeg)
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
				angleDegree += 1.0f;
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
				angleDegree -= 1.0f;
			}
			else
			{
				fixCount++;
			}
		}
	}

}