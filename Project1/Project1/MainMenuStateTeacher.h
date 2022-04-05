#pragma once 
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#pragma once
#include "SchoolYear.h"

using namespace sf;
using namespace tgui;
using namespace std;

void run_mainmenu_teacher(BackendGui& gui, tgui::String studentID);

void loadListofSchoolYears(SchoolYear*& schoolYear);
void addSpecificClass(SpecificClass*& nowClass, char classCode[], string year);
void loadListofSpecificClasses(SpecificClass*& nowClass, string className);

bool addComponents2(tgui::BackendGui& gui, tgui::String teacher_name  , SchoolYear*& schoolYears, tgui::String studentID);