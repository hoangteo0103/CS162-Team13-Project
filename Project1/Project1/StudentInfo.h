#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include "SchoolYear.h"
#include "Student.h"

void onStudentInfoSelected(tgui::Group& group_studentInfo, tgui::Group& group_student);
void init_group_student(tgui::Group& group_studentInfo);
void loadInfoWidget(tgui::Group& group_studentInfo, Student& student);