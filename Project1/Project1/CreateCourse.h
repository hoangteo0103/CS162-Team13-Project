#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include <vector>
#include "OpenFile.h"
#include "SchoolYear.h"
#include "Scoreboard.h"
#include "Student.h"

using namespace sf;
using namespace tgui;
using namespace std;



void onCreateCourseSelected(Group& group_create);
void init_group_create_course(Group& group_create); 
void loadcreateCoursewidget(Group& group_create, Semester*& semester);

