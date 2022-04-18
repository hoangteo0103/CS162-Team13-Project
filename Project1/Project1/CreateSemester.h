#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include <vector>
#include "OpenFile.h"
#include "SchoolYear.h"

using namespace sf;
using namespace tgui;
using namespace std;

void onCreateSemesterSelected(Group& group_create);
void init_group_create_semester(Group& group_create);
void loadcreateSemesterwidget(Group& group_create);
