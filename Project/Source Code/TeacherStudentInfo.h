#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include <vector>
#include "SchoolYear.h"
#include "StudentInfo.h"

using namespace sf;
using namespace tgui;
using namespace std;

void init_student_info(Group& group_studentInfo);
void loadStudentWidget(Group& group_studentInfo, SchoolYear*& curSchoolYear);
void onComboBoxesSelected(Group& group_studentInfo, tgui::String getSelectedItem);
void onItemDoubleClick(Group& group_studentInfo, Group& group_small_studentInfo, SchoolYear* curSchoolYear);