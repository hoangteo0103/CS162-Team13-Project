#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include <vector>
#include "SchoolYear.h"

using namespace sf;
using namespace tgui;
using namespace std;

void onStudentSBSelected(Group& group_studentSB, Group& group_student);
void init_groupSB(Group& group_studentSB);
void loadSBWidgets(Group& group_studentSB, SchoolYear*& schoolYear);
void onComboBoxCoursesSelected(Group& group_studentSB, tgui::String getSelectedItem);
void onComboBoxClassSelected(Group& group_studentSB, tgui::String getSelectedItem);