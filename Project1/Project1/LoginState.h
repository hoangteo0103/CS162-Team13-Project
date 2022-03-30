//#pragma once
//#ifndef LoginState_H
//#define LoginState_H
//#include<string.h>
//#include<fstream>
//#include "State.h"
//#include "Button.h"
//#include "AccountList.h"
//#include "TextBox.h"
//#include "MainMenuState.h"
//
//class LoginState :
//    public State
//{
//private:
//    map<std::string, Button* > buttons;
//    Font font;
//    //Textbox account, password; 
//    Texture textureLogo , textureHeader;
//    Sprite logoImage , headerlogoImage;
//    String accountInput, passwordInput; 
//    Text wrongPassText; 
//    map<std::string, Textbox* > loginText;
//    Account* listHead = nullptr, * listLast = nullptr;
//    bool isUpdated;
//    bool ok;
//    bool wrongPass = false; 
//    void initFonts();
//    void initButtons();
//
//public:
//    LoginState(RenderWindow* app, stack<State*>* states);
//    virtual ~LoginState();
//    // Functions
//    void updateKeyBinds(); 
//    void updateButtons();
//    void updateLoginText();
//    void endState();
//    void update(sf::Event* event = nullptr);
//    void render(RenderTarget* target = NULL);
//    void renderButtons(RenderTarget* target = NULL);
//
//    void loadAccount();
//    bool checkLoginAcc(std::string accnt, std::string psswrd);
//};
//
//
//#endif
#pragma once 
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "AccountList.h";
#include "MainMenuState.h"
using namespace sf;
using namespace tgui;
using namespace std;

bool run_login(BackendGui& gui);
void login(BackendGui& gui, tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, Account* accounts);
