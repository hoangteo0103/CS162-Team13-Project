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

void onCreateSelected(Group& group_create, Group& group_student);
void init_group_create(Group& group_create);
void loadcreatewidget(Group& group_create);
