#pragma once


class Title :public BaseScene
{
public:

    Title(SceneManager& manager);
    ~Title();

    void Initialize();
    void Update();
    void Draw();
private:
    int titleHandle;
    int time;
    int movieHandle;
    int backGroundHandle;
    int start_font;
    int alpha;
    int addAlpha;
    int alpha_bright;
    int font_back;
    int buttonSound;
    bool isPush;
    Camera* camera = NULL;
    Input* input = NULL;
    BlackOut* blackOut = NULL;
};

