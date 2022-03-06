#pragma once
#ifndef LoginState_H
#define LoginState_H
#include "State.h"
#include "Button.h"


class LoginState :
    public State
{
private:
    map<string, Button* > buttons;
    Font font;
    Texture textureLogo;
    Sprite logoImage;
    String accountInput, passwordInput; 
    Text accountText, passwordText; 

    bool isUpdated;
    bool ok;
    void initFonts();
    void initButtons();

public:
    LoginState(RenderWindow* app, stack<State*>* states);
    virtual ~LoginState();
    // Functions
    void updateKeyBinds(); 
    void updateButtons();
    void endState();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};
#endif

