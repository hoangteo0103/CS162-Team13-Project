#pragma once 
#include <queue>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "MainMenuState.h"
#include "LoginState.h"
#include "SchoolYear.h"
#include "Scoreboard.h"
#include "StudentInfo.h"
#include "CourseRegistration.h"
#include "Action.h"
using namespace sf;
using namespace tgui;
using namespace std;

void run_mainmenu(BackendGui& gui, tgui::String studentID);

void loadListofSchoolYears(SchoolYear*& schoolYear);
void addSpecificClass(SpecificClass*& nowClass, char classCode[], string year);
void loadListofSpecificClasses(SpecificClass*& nowClass, string className);

bool addComponents(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String studentID, tgui::Group& group_course, 
				tgui::Group& group_student, tgui::Group& group_scoreboard, tgui::Group& group_registration, tgui::Group& group_studentInfo);