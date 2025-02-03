#pragma once

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

	float addPosition_X;
	float addPosition_Z;
	int attackStack;
	bool is; 
	bool isSetPosition;

	static constexpr float speed = 1.5f;
	static constexpr float radius = 2;
public:

	EnemyCircleAttack();
	~EnemyCircleAttack();

	void Initialize();
	void Update();
	void Draw();
	void SetPosition(const VECTOR position) { bulletPosition = VGet(position.x, position.y, position.z); }
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

