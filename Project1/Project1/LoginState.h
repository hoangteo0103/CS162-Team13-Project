#pragma once
#ifndef LoginState_H
#define LoginState_H
#include<string.h>
#include<fstream>
#include "State.h"
#include "Button.h"
#include "AccountList.h"
#include "TextBox.h"
#include "MainMenuState.h"

class LoginState :
    public State
{
private:
    map<std::string, Button* > buttons;
    Font font;
    //Textbox account, password; 
    Texture textureLogo;
    Sprite logoImage;
    String accountInput, passwordInput; 
    Text wrongPassText; 
    map<std::string, Textbox* > loginText;
    Account* listHead = nullptr, * listLast = nullptr;
    bool isUpdated;
    bool ok;
    bool wrongPass = false; 
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
    void update(sf::Event* event = nullptr);
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

    void loadAccount();
    bool checkLoginAcc(std::string accnt, std::string psswrd);
};


#endif

