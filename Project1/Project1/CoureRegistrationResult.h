#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include "SchoolYear.h"
#include "Student.h"

using namespace sf;
using namespace tgui;
using namespace std;
void onCourseResultSelected(BackendGui& gui, SchoolYear* schoolYear, Student neededStudent);
void loadRegistrationResultWidget(BackendGui& gui , queue<pair<SchoolYear*, int>> &curSchoolYear, Student& neededStudent);