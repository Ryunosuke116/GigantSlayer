#pragma once
#include "Effect.h"
#include "EnemyCircleAttack.h"
class EnemyBullet
{
private:
    VECTOR position;            //�G�̍��W
    VECTOR bulletSpeed;         //�e��
    VECTOR playerPos;           //�v���C���[�̍��W
    VECTOR futurePosition;      //�v���C���[�̖������W
    VECTOR effectPosition;      //�G�t�F�N�g�̃|�W
    VECTOR fellPosition;        //�������|�W�V����
    VECTOR velocity;         //���x
    int effectPlayStack;        //�G�t�F�N�g�Đ�����
    int positionStack;    //�ړ������
    bool isAttack;
    bool isPlayerMove;
    bool isLeftMove;
    bool isRightMove;
    bool isTopMove;
    bool isBottomMove;
    bool isEffect;          //�G�t�F�N�g���o����
    bool isEmerge;          //�o�������邩
    bool isCircleBullet;    //�T�[�N���U�������邩
    bool isSetUpMotion;     //�U�����[�V�����ɓ�������
    float playerMoveSpeed;
    float bulletSpeed_Y;  
    float scale;
    Effect* effect;
    Effect* bulletColor;
    static constexpr float theta    = 30;               //����p�x�̏��
    static constexpr float speed    = 4.0f;             //���x
    static constexpr float radius   = 5.0f;             //���a
    static constexpr float circleAttackBulletSpeed = 0.5f;

    static constexpr int maxPositionStack = 50;

public:

    EnemyBullet();
    ~EnemyBullet();

    void Initialize(const VECTOR EnemyPosition);
    void Update(const VECTOR EnemyPosition, 
        EnemyCircleAttack& circleAttack);
    void Draw();
    void Move(const VECTOR EnemyPosition,EnemyCircleAttack& circleAttack);
    void BulletMove();
    void AttackDesignation(const VECTOR EnemyPosition);
    void SetPlayerMoveSpeed(float moveSpeed);
    void PlayerMovementPrediction();
    void SetIsPlayerMove(bool isMove);
    void SetIsPlayerMoveDirection(bool isTopMove, bool isBottomMove, bool isRightMove, bool isLeftMove);
    void SetPlayerPosition(VECTOR& getPosition);
    void SetPosition(VECTOR& getPosition);
    void SwitchingIsCircleBullet();
    VECTOR GetPosition() { return position; }
    VECTOR GetFellPosition() { return fellPosition; }
    bool GetIsEmerge() { return isEmerge; }
    float GetRadius(){ return radius;}
    void SetIsEmerge(const bool value) { isEmerge = value; }
    void SetIsCircleBullet(const bool value) { isCircleBullet = value; }
    void SetIsAttack(const bool value) { isAttack = value; }
    void SetIsSetUpMotion(const bool value) { isSetUpMotion = value; }
};

