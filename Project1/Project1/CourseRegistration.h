#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include "SchoolYear.h"
#include "Student.h"

using namespace sf;
using namespace tgui;
using namespace std;

void onCorseRegistrationSelected(tgui::Group& group_registration, tgui::Group& group_student);
void init_group_registration(Group& group_registration);
void loadRegistrationWidget(Group& group_registration, queue<pair<SchoolYear*, int>>& curSchoolYear, Student& neededStudent);