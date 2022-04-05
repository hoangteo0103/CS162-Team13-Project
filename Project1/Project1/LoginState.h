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
