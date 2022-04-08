#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include <vector>
#include "SchoolYear.h"

using namespace sf;
using namespace tgui;
using namespace std;

void onScoreboardSelected(Group& group_scoreboard, Group& group_student);
void init_group(Group& group_scoreboard);
void loadwidget(Group& group_scoreboard, queue<pair<SchoolYear*, int>> curSchoolYear);