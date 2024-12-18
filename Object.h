#pragma once
#include "DxLib.h"
#include"EffekseerForDXLib.h"
#include <vector>
#include "Calculation.h"
#include "Effect.h"
#include "Input.h"
#include "Enemy.h"

class Object
{
private:
    VECTOR position;
    VECTOR addPosition;
    VECTOR subPosition;
    float radius;
    int time;
    bool isHitPlayer;
    bool isHit;
    bool isGetPosition;
    bool isObject;      //�o�������ǂ���
    bool isHitBreath;   //�u���X�ɓ���������
    bool isCanCatch;    //���߂邩
    static constexpr float speed = 3.0f;        //����
    Effect* effect;
    static constexpr int objectNumber = 4;      //�I�u�W�F�N�g�̐�
public:

    Object();
    ~Object();

    void Initialize(Enemy& enemy);
    void Update(Enemy& enemy, Calculation& calculation, const Input& input);
    void Draw();
    void WhichOnObject(Enemy& enemy);
    void WhichOffObject(const bool& isEmerge);

    VECTOR GetPosition() { return position; }
    void SetPosition(VECTOR newPosition) { position = newPosition; }
    float GetRadius() { return radius; }
    //�n��
    bool GetIsObject() { return isObject; }
    bool GetIsCanCatch() { return isCanCatch; }
    void PlayerIsHit(const bool& isHit);
    void SetIsCanCatch(const bool& value);
    void DirectionCalculation(const VECTOR comparisonPosition);

};

