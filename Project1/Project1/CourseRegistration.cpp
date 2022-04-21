#include "CourseRegistration.h"

void onCorseRegistrationSelected(tgui::Group& group_registration, tgui::Group& group_student) {
	group_registration.setVisible(true);
	group_student.setVisible(false);
}

void init_group_registration(Group& group_registration) {
	group_registration.loadWidgetsFromFile("CourseRegistrationForm.txt");
}

void loadRegistrationWidget(Group& group_registration, queue<pair<SchoolYear*, int>>& curSchoolYear, Student& neededStudent) {
	init_group_registration(group_registration);

	group_registration.get<tgui::ListView>("ListView1")->addColumn("Course ID", 100, tgui::ListView::ColumnAlignment::Center);
	group_registration.get<tgui::ListView>("ListView1")->addColumn("Course", 210, tgui::ListView::ColumnAlignment::Center);
	group_registration.get<tgui::ListView>("ListView1")->addColumn("1st Schedule", 150, tgui::ListView::ColumnAlignment::Center);
	group_registration.get<tgui::ListView>("ListView1")->addColumn("2nd Schedule", 150, tgui::ListView::ColumnAlignment::Center);
	group_registration.get<tgui::ListView>("ListView1")->addColumn("Teacher", 380, tgui::ListView::ColumnAlignment::Center);

	SchoolYear* schoolYear = curSchoolYear.front().first;
	Semester* curSemester = schoolYear->nowSemester;

	int cnt = 0;
	for (Semester* i = schoolYear->nowSemester; i; i = i->nextSemester) {
		cnt++;
	}
	
	tgui::String curDir = "SchoolYears/" + tgui::String(schoolYear->startYear) + '-' + tgui::String(schoolYear->endYear) + '/';
	curDir += "Semester" + tgui::String(cnt) + "/Courses/";

	int curHeight = 0;
	for (Course* i = curSemester->nowCourse; i; i = i->nextCourse) {
		curHeight++;
		vector<tgui::String> tmp;
		tmp = { tgui::String(i->courseID), tgui::String(i->courseName), tgui::String(i->getFirstSessionDate()), tgui::String(i->getSecondSessionDate()), tgui::String(i->teacherName)};
		group_registration.get<tgui::ListView>("ListView1")->addItem(tmp);
		tgui::String order = "CheckBox" + tgui::String(curHeight);
		group_registration.get<tgui::CheckBox>(order.toStdString())->setVisible(true);
	}
}