#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include <vector>
#include "SchoolYear.h"

using namespace sf;
using namespace tgui;
using namespace std;

void onTeacherScoreboardSelected(Group& group_scoreboard, Group& group_student);
void init_scoreboard_group(Group& group_scoreboard);
void loadScoreBoardWidget(Group& group_scoreboard, SchoolYear*& schoolYear);