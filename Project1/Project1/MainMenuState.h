#pragma once
#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "fstream"
#include "sstream"
#include "State.h"
#include "Button.h"
#include "SchoolYear.h"
class MainMenuState :
    public State
{
private:
    // Graphics 
    Texture t;
    Sprite background;
    Font font;
    map<string, Button* > buttons;
    void initFonts();
    void initButtons();
    // Data 
    SchoolYear *schoolYear;
    SpecificClass *nowClass;
public:
    MainMenuState(RenderWindow* app, stack<State*>* states);
    virtual ~MainMenuState();
    // Functions
    void updateKeyBinds();
    void updateButtons();
    void endState();
    void update(sf::Event *event = nullptr);
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

    // School functions 
    void addSpecificCLass(SpecificClass*& nowClass, char classCode[NAMELENGTH]);
    void loadListofSpecificClasses(SpecificClass*& nowClass);


};

#endif // MAINMENUSTATE_H






