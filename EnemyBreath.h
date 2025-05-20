#pragma once

class Effect;

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
	float addPosition_X;		//x�����ɑ΂�����Z
	float addPosition_Z;		//y�����ɑ΂�����Z
	int attackStack;			//���̋��𓮂����Ă��邩		
	int attackNumber;			//���񋅂𓮂�����
	int fixCount;				//�U�����Œ肷��
	int effectPlayStack;		//�G�t�F�N�g�Đ�����
	int SEHandle;
	bool isStopAdd;				//���Z���邩�ǂ���
	bool isDirection;			//������ς��邩
	bool isEffect;
	bool isAttack;
	std::vector<Breath> breaths;
 
	static constexpr int breathNumber = 126;
	static constexpr float speed = 2.0f;

public:

	EnemyBreath();
	~EnemyBreath();

	void Initialize();
	void Update();
	void Draw();
	void EndBreath();
	void Rotation(VECTOR playerPos, VECTOR enemyPos);
	void Direction(VECTOR& addPosition);
	void ResetPosition(const VECTOR position);
	int Count;

	//------------------------------------------------------------//
	// �Q�b�^�[
	//-----------------------------------------------------------//
	bool GetIsAttack() { return isAttack; }


	//-------------------------------------------------------------//
	// �Z�b�^�[
	//-------------------------------------------------------------//
	void SetIsAttack(const bool value) { isAttack = value; }
	void SetPosition(const VECTOR position) { formerPosition = VGet(position.x, position.y, position.z - 10.0f); }
	
	const std::vector<Breath>& getBreath() const
	{
		return breaths;
	}
};

