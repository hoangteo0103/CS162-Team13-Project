#pragma once 
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "SchoolYear.h"
#include "Action.h"
#include "CreateRegistration.h"
#include "TeacherScoreboard.h"
#include "TeacherStudentInfo.h"
#include "ClassScoreboard.h"

using namespace sf;
using namespace tgui;
using namespace std;

void run_mainmenu_teacher(BackendGui& gui, tgui::String teacherName, int dm);
void loadListofSchoolYears(SchoolYear*& schoolYear);
void addSpecificClass(SpecificClass*& nowClass, char classCode[], string year);
void loadListofSpecificClasses(SpecificClass*& nowClass, string className);

bool addComponents2(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String teacherName, tgui::Group& group_course,
    tgui::Group& group_student, tgui::Group& group_scoreboard, tgui::Group& group_studentSB, tgui::Group& group_studentInfo, tgui::Group& group_small_studentInfo, tgui::Group& group_create);