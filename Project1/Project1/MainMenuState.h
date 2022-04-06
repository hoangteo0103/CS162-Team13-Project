#pragma once 
#include <queue>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "MainMenuState.h"
#include "SchoolYear.h"

using namespace sf;
using namespace tgui;
using namespace std;

void run_mainmenu(BackendGui& gui, tgui::String studentID);

void loadListofSchoolYears(SchoolYear*& schoolYear);
void addSpecificClass(SpecificClass*& nowClass, char classCode[], string year);
void loadListofSpecificClasses(SpecificClass*& nowClass, string className);

bool addComponents(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String studentID);