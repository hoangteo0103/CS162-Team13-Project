#pragma once
#ifndef LoginState_H
#define LoginState_H
#include "State.h"
#include "Button.h"
#include "TextBox.h"


class LoginState :
    public State
{
private:
    map<string, Button* > buttons;
    Font font;
    //Textbox account, password; 
    Texture textureLogo;
    Sprite logoImage;
    String accountInput, passwordInput; 
    Text accountText, passwordText; 
    map<string, Textbox* > loginText;
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
    void updateLoginText();
    void endState();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);
};
#endif

