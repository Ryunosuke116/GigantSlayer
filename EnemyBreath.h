#pragma once
#include "Effect.h"



class EnemyBreath
{
private:
	struct Breath
	{
		VECTOR position;		//���̃|�W�V����
		VECTOR addPosition;		//���𓮂������߂̉��Z�|�W�V����
		VECTOR effectPosition;		
		bool isAdd;				//���Z���邩�ǂ���
		bool isStop;			//�~�߂邩�ǂ���
		float radius;			//���̔��a
		Effect* effect;				//�G�t�F�N�g�N���X
	};
	//Breath breath[42];
	Breath breath;				//���̍\����
	VECTOR formerPosition;		//���̃|�W�V����
	VECTOR effectPosition;		//�G�t�F�N�g�̃|�W�V����
	VECTOR rotation;			//��]
	Effect* effect;				//�G�t�F�N�g�N���X
	float radius;				//���a
	float addRotation_Y;			//���Z����
	float addPosition_X;		//x�����ɑ΂�����Z
	float addPosition_Z;		//y�����ɑ΂�����Z
	int attackStack;			//���̋��𓮂����Ă��邩		
	int attackNumber;			//���񋅂𓮂�����
	int fixCount;				//�U�����Œ肷��
	int effectPlayStack;		//�G�t�F�N�g�Đ�����
	bool isStopAdd;				//���Z���邩�ǂ���
	bool isDirection;			//������ς��邩
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

