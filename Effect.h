#pragma once

class Effect
{
private:
  
    VECTOR position;
    int time;
    int playingEffectHandle;
    int resourceHandle;
    
    
public:
    Effect();
    ~Effect();

    void Initialize(const char* path, float magnification, const VECTOR& objectPosition);
    void PositionUpdate(const VECTOR& objectPosition);
    void PlayEffectUpdate();
    void Draw();
    void SetPosition(const VECTOR setPosition);
    void SetRotation(VECTOR setPosition);
    void SetScale(VECTOR scale);
    void SetSpeed(float speed);
    void PlayEffect();
    void StopEffect();
};

