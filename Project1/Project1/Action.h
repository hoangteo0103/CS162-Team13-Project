#pragma once
#include <queue>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "MainMenuState.h"
#include "LoginState.h"
#include "SchoolYear.h"
#include "Scoreboard.h"
#include "StudentInfo.h"
using namespace sf;
using namespace tgui;
using namespace std;

void onParticipants(Group& group_course, Course*& curCourse);
void onClickedLogout(BackendGui& gui);
void onTabSelected(tgui::BackendGui& gui, tgui::String* curSelectedTab, vector<tgui::Group*>* vc, tgui::String selectedTab);
void onItemSelected(tgui::Group& group_course, SchoolYear* schoolYears, Course*& curCourse, Student student, tgui::String selectedItem);
void showGroupCourse(Group& group_course, bool check);
// Teacher action 
void onTabSelected2(tgui::BackendGui& gui, tgui::String* curSelectedTab, vector<tgui::Group*>* vc, tgui::String selectedTab);
void onItemSelected2(tgui::Group& group_course, SchoolYear* schoolYears, Course*& curCourse, tgui::String selectedItem);

 