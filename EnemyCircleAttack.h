#pragma once
#include "Effect.h"

class EnemyCircleAttack
{
private:

	struct CircleAttack
	{
		VECTOR position;
		VECTOR addPosition;
		VECTOR effectPosition;
		Effect* effect;
	};
	CircleAttack circleAttack;
	VECTOR bulletPosition;
	VECTOR enemyPosition;
	float radius;
	float addPosition_X;
	float addPosition_Z;
	int stack;
	int attackStack;
	bool is; 
	bool isSetPosition;

	static constexpr float speed = 1.5f;
public:

	EnemyCircleAttack();
	~EnemyCircleAttack();

	void Initialize();
	void Update();
	void Draw();
	void CircumferenceCalculation(float& x, float& z);
	void SetPosition(const VECTOR position);
	void SetEnemyPosition(const VECTOR position);
	void ResetPosition(const VECTOR position);
	float GetRadius() { return radius; }
	std::vector<CircleAttack> circleAttacks;

	const std::vector<CircleAttack>& getCircleAttacks() const
	{
		return circleAttacks;
	}


	bool isAttack;
	int Count;
};
