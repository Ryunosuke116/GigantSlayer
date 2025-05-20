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
    int buttonSound;
    float alpha;
    float addAlpha;
    float alpha_white;
    float addAlpha_white;
    float alpha_black;
    float addAlpha_black;
    bool isAdd;
    Input* input;
    BlackOut* blackOut;
};

