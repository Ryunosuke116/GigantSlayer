#pragma once

class Object;
class Enemy;
class Calculation;
class Effect;
class Input;
class Map;

class Player
{
private:
    static constexpr float  radius      = 2;        //���a    
    static constexpr float  AttackSpeed = 0.65f;     //�e�̑��x
    static constexpr float	MoveSpeed   = 0.4f;	    // �ړ����x
    static constexpr float  slowMoveSpeed = 0.3f;   //�ړ����x
    static constexpr float	JumpPower   = 1.1f;	    // �W�����v��
    static constexpr float	Gravity     = 0.06f;	// �d��
    static constexpr float  AttackGravity = 0.15f;  //�U���̏d��
    static constexpr float	AngleSpeed  = 0.2f;	    // �p�x�ω����x
    static constexpr float  maxRange    = 33.0f;    //�ő�͈�
    static constexpr float	ShadowSize = 3.0f;	// �e�̑傫��
    static constexpr float	ShadowHeight = 10.0f;	// �e�������鍂��
    static constexpr int objectNumber = 4;      //�I�u�W�F�N�g�̐�

    static constexpr int    die = 0;            //�|���
    static constexpr int    down = 7;           //�_�E������
    static constexpr int    standUp = 16;        //�����オ��
    static constexpr int    stand = 14;          //�ҋ@
    static constexpr int    run = 12;           //����
    static constexpr int    jump = 8;           //�W�����v
    static constexpr int    stop = 17;           //�~�܂�
    static constexpr int    pickUp = 10;         //�E��

    static constexpr int    stand_Hold = 15;
    static constexpr int    run_Hold = 13;
    static constexpr int    jump_Hold = 9;
    static constexpr int    stop_Hold = 18;
    static constexpr int    pickUp_Hold = 11;

    VECTOR position;
    VECTOR targetMoveDirection;	// ���f���������ׂ������̃x�N�g��
    VECTOR objectPosition;
    VECTOR keepTargetMoveDirection;
    VECTOR effectPosition;
    VECTOR topSpherePosition;
    VECTOR bottomSpherePosition;
    VECTOR closePosition;          //�v���C���[�Ƌ��̍ł��߂��_
    VECTOR testPosition;
    VECTOR attackPosition;         //�U���̋�

    Effect* effect;
    Effect* attackEffect;

    int shadowHandle;
    int effectResourceHandle;
    int modelHandle;
    int attachIndex;            //�Đ����̃��[�V�����ԍ�
    int motionNum;
    int stock;
    int attackEffectTime;
    int playingEffectHandle;
    int motionNumber;           //���[�V�����ԍ�
    int HpHandle;      
    int HP;

    float currentJumpPower;		// �x�������̑��x
    float totalTime;            //���[�V�����̑��Đ�����
    float playTime;             //���݂̍Đ�����
    float angle;					// ���f���������Ă�������̊p�x
    float attackSpeedY;         //�U���d��
    float invincibleTime;       //���G����

    bool isMove;                    //��������
    bool isHitEnemyAttack;          //Enemy�̍U���ɓ������Ă��邩
    bool isJump;                    //�W�����v������
    bool isOnGround;                //�ڒn���Ă��邩
    bool isPushKey;                 //�L�[�������Ă��邩
    bool isEffect;                  //�G�t�F�N�g���łĂ��邩
    bool isHitObject[objectNumber];               //�I�u�W�F�N�g���������Ă��邩
    bool isObjectHitEnemy;          //�U����enemy�ɓ���������
    bool isChangeMotion;            //���[�V�����ύX���邩
    bool isPlayTime;
    bool isAttackHold;              //�U����ێ����Ă��邩
    bool isInvincible;              //���G��
    bool isDisplay;                 //�\�����邩


public:

    Player();
    ~Player();

    void Initialize();                                       //������
    void Update(Calculation& calculation,                   //�X�V
        std::array<Object*, 4> object,
        const Input& input, Enemy& enemy);
    void StartUpdate();
    void Draw(const Map& map);
    void UpdateAngle();
    void Attack(const Input& input);
    void AttackHitCheck(Enemy& enemy, Calculation& calculation);
    void Move(const Input& input, VECTOR& moveVec);
    void Jump(const Input& input, VECTOR& moveVec);

    void EnemyHitCheck(Enemy& enemy, Calculation& calculation);
    bool ObjectHitCheck(const VECTOR objectPosition,
        const float radius, Calculation& calculation);
    void Down();
    void PickUpObject(Object& object, const Input& input);
    ///////////////////////////////////////////////
    //���[�V�����֘A
    ///////////////////////////////////////////////
    void MotionUpdate();
    void ChangeMotion(int motionNum);
    void Motion_HoldorUnHold(int motionNum,int holdMotionNum);

    ////////////////////////////////////////////////
    // �Q�b�^�[
    ///////////////////////////////////////////////
    int GetHP() { return HP; }
    int GetMotionNum() { return motionNum; }
    float GetMoveSpeed() { return MoveSpeed; }
    bool GetIsMove() { return isMove; }
    bool GetIsPushKey() { return isPushKey; }
    VECTOR GetTargetMoveDirection_Norm() { return VNorm(targetMoveDirection); }
    VECTOR GetPosition() const { return position; }
    VECTOR GetTopPosition()const { return topSpherePosition; }

    //-------------------------------------------//
    // �Z�b�^�[
    //-------------------------------------------//
    void SetPosition(VECTOR newPosition) { position = newPosition; }
    void SetIsPushKey(bool newIsPushKey) { isPushKey = newIsPushKey; }

};
