#pragma once
#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "State.h"
#include "Button.h"
#include "TextBox.h"
class MainMenuState :
    public State
{
private:
    Texture t;
    Sprite background;
    Font font;
    map<string, Button* > buttons;
    map<string, Textbox*> textboxes;
    bool werePressed; //Only show textboxed when this is true
    void initFonts();
    void initButtons();

public:
    MainMenuState(RenderWindow* app, stack<State*>* states);
    virtual ~MainMenuState();
    // Functions
    void updateKeyBinds();
    void updateButtons();
    void updateTextBoxes();
    void endState();
    void update(sf::Event *event = nullptr);
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};

#endif // MAINMENUSTATE_H






