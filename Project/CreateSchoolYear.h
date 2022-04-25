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

void onCreateYearSelected(Group& group_create);
void init_group_create_year(Group& group_create);
void loadcreateYearwidget(Group& group_create);
