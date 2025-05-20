#pragma once


class GameOver : public BaseScene
{
public:

    GameOver(SceneManager& manager);
    ~GameOver();

    void Initialize();
    void Update();
    void Draw();

private:

    int continue_font = NULL;
    int titleBack_font = NULL;
    int gameOver_font;
    int font_back;
    int arrow;
    int select;
    int buttonSound;
    float alpha;
    float alpha_arrow;
    float addAlpha_arrow;
    float addAlpha;
    float addAlpha_blackOut;
    bool isAdd;
    bool isSceneChange;
    Input* input = NULL;
    BlackOut* blackOut = NULL;
};

