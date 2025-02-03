#pragma once


class GameClear : public BaseScene
{
public:

    GameClear(SceneManager& manager);
    ~GameClear();

    void Initialize();
    void Update();
    void Draw();

private:
    int clear_font;
    int font_back;
    int titleBack_font;
    float alpha;
    float addAlpha;
    Input* input;
    BlackOut* blackOut;
};

