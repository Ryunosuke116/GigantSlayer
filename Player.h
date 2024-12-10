#pragma once
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Calculation.h"
#include "Object.h"
#include "Input.h"
#include "Effect.h"
#include"Map.h"


class Player
{
private:
    static constexpr float  radius      = 2;        //���a    
    static constexpr float  AttackSpeed = 0.65f;     //�e�̑��x
    static constexpr float	MoveSpeed   = 0.5f;	    // �ړ����x
    static constexpr float  slowMoveSpeed = 0.3f;   //�ړ����x
    static constexpr float	JumpPower   = 1.5f;	    // �W�����v��
    static constexpr float	Gravity     = 0.08f;	// �d��
    static constexpr float  AttackGravity = 0.15f;  //�U���̏d��
    static constexpr float	AngleSpeed  = 0.4f;	    // �p�x�ω����x
    static constexpr float  maxRange    = 33.0f;    //�ő�͈�
    static constexpr float	ShadowSize = 3.0f;	// �e�̑傫��
    static constexpr float	ShadowHeight = 10.0f;	// �e�������鍂��
    static constexpr int objectNumber = 4;      //�I�u�W�F�N�g�̐�

    static constexpr int    down = 0;           //�_�E������
    static constexpr int    standUp = 1;        //�����オ��
    static constexpr int    jump = 13;           //�W�����v
    static constexpr int    stop = 10;           //�~�܂�
    static constexpr int    stand = 2;          //�ҋ@
    static constexpr int    run = 7;           //����
    static constexpr int    pickUp = 4;         //�E��

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
    


public:

    Player();
    ~Player();

    void Initialize();                                       //������
    void Update(Calculation& calculation,                   //�X�V
        std::array<Object*, 4> object,
        const Input& input, Enemy& enemy);
    void Draw(const Map& map);
    void ChangeMotion(int motionNum);
    void UpdateAngle();
    void Attack(const Input& input);
    void AttackHitCheck(Enemy& enemy, Calculation& calculation);
    void Move(const Input& input, VECTOR& moveVec);
    void Jump(const Input& input, VECTOR& moveVec);
    void GetPosition(VECTOR& setPosition);
    void EnemyHitCheck(Enemy& enemy, Calculation& calculation);
    bool ObjectHitCheck(const VECTOR objectPosition,
        const float radius, Calculation& calculation);
    void Down();
    void MotionUpdate();
    void PickUpObject(Object& object, const Input& input);
    void DrawShadow(const Map& map, VECTOR& position);
  
    float GetMoveSpeed() { return MoveSpeed; }
    bool GetIsMove() { return isMove; }
    VECTOR GetPosition() const { return position; }
    int GetHP() { return HP; }

};
