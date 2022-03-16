#pragma once
#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "State.h"
#include "Button.h"
class MainMenuState :
    public State
{
private:
    Texture t;
    Sprite background;
    Font font;
    map<string, Button* > buttons;
    void initFonts();
    void initButtons();

public:
    MainMenuState(RenderWindow* app, stack<State*>* states);
    virtual ~MainMenuState();
    // Functions
    void updateKeyBinds();
    void updateButtons();
    void endState();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};

#endif // MAINMENUSTATE_H






