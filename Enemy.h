#pragma once
#include "EnemyBullet.h"
#include "EnemyCircleAttack.h"
#include"EnemyBreath.h"


class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Initialize();
    void Update();
    void Draw();
    VECTOR GetBulletPosition() { return bulletPosition; }
    VECTOR GetTopPosition() { return topPosition; }
    VECTOR GetBottomPosition() { return bottomPosition; }
    
    void SetIsPlayerAttackHit(const bool value) { isPlayerAttackHit = value; }
    void ActionFlow(EnemyBullet& bullet, EnemyCircleAttack& circleAttack,
        EnemyBreath& breath);
    void GetPosition(VECTOR& setPosition);
    void SetPosition(const VECTOR& getPosition);
    void SetPlayerMoveSpeed(float moveSpeed);
    void SetIsPlayerMove(bool isMove);
    void SetIsPlayerMoveDirection(bool isTopMove, bool isBottomMove, bool isRightMove, bool isLeftMove);
    
    void AttackDesignation();
    void PlayerMovementPrediction();
    void Order(EnemyBullet& bullet, EnemyBreath& breath);
    //���[�V�����֘A
    void ChangeMotion(int numberNum);
    void MotionUpdate();

    //�Q�b�^�[
    int GetHP() { return HP; }
    float GetRadius() { return radius; }

    // �C���X�^���X��
    EnemyBullet* bullet = new EnemyBullet();
    EnemyCircleAttack* circleAttack = new EnemyCircleAttack();
    EnemyBreath* breath = new EnemyBreath();
    
private:
    
    //���[�V�����֘A
    int modelHandle;                    //���f��
    int motionNum;
    int attachIndex;                    //�Đ����̃��[�V�����ԍ�
    int orderNumber;                    //�s�����鏇
    int bulletNumber;                   //���݂̍U����
    int maxBulletNumber;                //�ő�U����
    int HP;
    float totalTime;                    //���[�V�����̑��Đ�����
    
    
    float standTime;                    //�ҋ@����
    float playTime;                     //���݂̍Đ�����
    float addPlayTime;
    bool isAttack;                      //�U�����邩
    bool isPlayerAttackHit;              //�U���𓖂Ă�ꂽ��
    bool isKnockback;                   //�̂���������
    bool isPlayerMove;                  //�v���C���[��������
    bool isLeftMove;                    //���ɓ�������
    bool isRightMove;                   //�E�ɓ�������
    bool isTopMove;                     //��ɓ�������
    bool isBottomMove;                  //���ɓ�������
    bool isBulletNumber;                //����U�����邩
    VECTOR topPosition;                    //Enemy�̃|�W�V����
    VECTOR bottomPosition;           //���̃|�W�V����
    VECTOR AttackSpherePosition;        //�U���̃|�W�V����
    VECTOR bulletSpeed;                 //�e�̑��x
    VECTOR bulletPosition;              //�e�̃|�W�V����
    VECTOR bulletMotionPosition;        //�e�U�����̃��f���|�W�V����
    VECTOR playerPos;                   //�v���C���[�̃|�W�V����
    VECTOR futurePosition;              //�����̃|�W�V����
    float bulletPositionStack;          
    float radius;                       //���̔��a
    float playerMoveSpeed;              //�v���C���[�̑��x
    float bulletSpeed_Y;                //�e�̏c�ɓ������x

    static constexpr int knockback = 1;         //�̂�����
    static constexpr int jump = 4;              //�W�����v  
    static constexpr int turn = 5;              //���
    static constexpr int breathAttack = 6;      //�u���X
    static constexpr int bulletAttack = 7;      //�e�U��
    static constexpr int stand = 16;             //�ҋ@
};

