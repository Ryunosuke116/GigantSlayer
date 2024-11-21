#pragma once
#include "Effect.h"



class EnemyBreath
{
private:
	struct Breath
	{
		VECTOR position;		//球のポジション
		VECTOR addPosition;		//球を動かすための加算ポジション
		VECTOR effectPosition;		
		bool isAdd;				//加算するかどうか
		bool isStop;			//止めるかどうか
		float radius;			//球の半径
		Effect* effect;				//エフェクトクラス
	};
	//Breath breath[42];
	Breath breath;				//球の構造体
	VECTOR formerPosition;		//元のポジション
	VECTOR effectPosition;		//エフェクトのポジション
	VECTOR rotation;			//回転
	Effect* effect;				//エフェクトクラス
	float radius;				//半径
	float addRotation_Y;			//加算成分
	float addPosition_X;		//x成分に対する加算
	float addPosition_Z;		//y成分に対する加算
	int attackStack;			//何個の球を動かしているか		
	int attackNumber;			//何回球を動かすか
	int fixCount;				//攻撃を固定する
	int effectPlayStack;		//エフェクト再生時間
	bool isStopAdd;				//加算するかどうか
	bool isDirection;			//向きを変えるか
	bool isEffect;
 
	static constexpr int breathNumber = 84;

public:

	EnemyBreath();
	~EnemyBreath();

	void Initialize();
	void Update();
	void Draw();
	void CircumferenceCalculation(float& x, float& z);
	void Rotation(VECTOR playerPos, VECTOR enemyPos);
	void SetPosition(const VECTOR position);
	void Direction(VECTOR& addPosition);
	void ResetPosition(const VECTOR position);
	void SetIsAttack(const bool value) { isAttack = value; }
	std::vector<Breath> breaths;
	bool isAttack;
	int Count;
	
	const std::vector<Breath>& getBreath() const
	{
		return breaths;
	}
};

