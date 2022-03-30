//#pragma once
//#ifndef MAINMENUSTATE_H
//#define MAINMENUSTATE_H
//#include "fstream"
//#include "sstream"
//#include "State.h"
//#include "Button.h"
//#include "SchoolYear.h"
//class MainMenuState :
//    public State
//{
//private:
//    // Graphics 
//    Texture t, textureBackground;
//    Sprite background;
//    Font font;
//    map<string, Button* > buttons;
//    void initFonts();
//    void initButtons();
//    // Data 
//    SchoolYear *schoolYear;
//    SpecificClass *nowClass;
//public:
//    std::string curStudentID; //Current logging in student
//
//    MainMenuState(RenderWindow* app, stack<State*>* states, std::string sID);
//    virtual ~MainMenuState();
//    // Functions
//    void updateKeyBinds();
//    void updateButtons();
//    void endState();
//    void update(sf::Event *event = nullptr);
//    void render(RenderTarget* target = nullptr);
//    void renderButtons(RenderTarget* target = nullptr);
//
//    // School functions 
//    //void addSpecificCLass(SpecificClass*& nowClass, char classCode[]);
//    //void loadListofSpecificClasses(SpecificClass*& nowClass, string className);
//    void loadListofSchoolYears(SchoolYear*& schoolYear);
//};
//
//#endif // MAINMENUSTATE_H
//
//
//
//
//
//
#pragma once 
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
using namespace sf;
using namespace tgui;
using namespace std;

void run_mainmenu(BackendGui& gui);