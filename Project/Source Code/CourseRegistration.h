#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <queue>
#include "SchoolYear.h"
#include "Student.h"

using namespace sf;
using namespace tgui;
using namespace std;

struct TemporaryData {
	int no = 0, ID = 0;
	int mMark = 0, fMark = 0, oMark = 0, tMark = 0;
	char fName[FULLNAMELENGTH];
	
	TemporaryData(){}

	TemporaryData(int a, int b, int mM, int fM, int oM, int tM, char name[]) {
		no = a; ID = b;
		mMark = mM; fMark = fM; oM = mMark; tMark = tM;
		for (int i = 0; i < strlen(name); i++) {
			fName[i] = name[i];
		}
		fName[strlen(name)] = '\0';
	}
};

void onCorseRegistrationSelected(tgui::Group& group_registration, tgui::Group& group_student);
void init_group_registration(Group& group_registration);
void loadRegistrationWidget(Group& group_registration, queue<pair<SchoolYear*, int>>& curSchoolYear, Student& neededStudent);