#include "CoureRegistrationResult.h"
void onCourseResultSelected(BackendGui& gui, SchoolYear *schoolYears, Student neededStudent)
{
	
	gui.get<Group>("group_student")->setVisible(false); 
	gui.get<Group>("group_registration_result")->setVisible(true);

	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->removeAllColumns();
	
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("Course ID", 103, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("Course", 220, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("1st Schedule", 165, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("2nd Schedule", 165, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("Teacher", 240, tgui::ListView::ColumnAlignment::Center);
	queue<pair<SchoolYear*, int>> curSchoolYear;
	string studentName = neededStudent.firstName;
	studentName += ' ';
	studentName+=neededStudent.lastName;
	for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
		tgui::String years = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

		//cerr << years << '\n';
		int ID;
		for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
			if (j->findStudentByName(studentName, ID)) {
				curSchoolYear.push(make_pair(i, ID));
				break;
			}
		}
	}
	SchoolYear* schoolYear = curSchoolYear.front().first;
	Semester* curSemester = schoolYear->nowSemester;
	
	int cnt = 0;
	for (Semester* i = schoolYear->nowSemester; i; i = i->nextSemester) {
		cnt++;
	}
	tgui::String curDir = "SchoolYears/"
		+ tgui::String(schoolYear->startYear) + '-' + tgui::String(schoolYear->endYear) + '/';
	curDir += "Semester" + tgui::String(cnt) + "/Courses/";


	int curHeight = 0;
	for (Course* i = curSemester->nowCourse; i; i = i->nextCourse) {
		curHeight++;
		vector<tgui::String> tmp;
		tmp = { tgui::String(i->courseID), tgui::String(i->courseName), tgui::String(i->getFirstSessionDate()), tgui::String(i->getSecondSessionDate()), tgui::String(i->teacherName) };

		for (Student* j = i->nxtStudent; j; j = j->nextStudent) {
			if (j->studentID == neededStudent.studentID) {
				gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addItem(tmp);
				break;
			}
		}
	}
}
void loadRegistrationResultWidget(BackendGui& gui , queue<pair<SchoolYear*, int>>& curSchoolYear, Student& neededStudent) {
	gui.get<Group>("group_registration_result")->removeAllWidgets();
	gui.get<Group>("group_registration_result")->loadWidgetsFromFile("CourseRegistrationResultForm.txt");
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("Course ID", 103, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("Course", 220, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("1st Schedule", 165, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("2nd Schedule", 165, tgui::ListView::ColumnAlignment::Center);
	gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addColumn("Teacher", 340, tgui::ListView::ColumnAlignment::Center);

	SchoolYear* schoolYear = curSchoolYear.front().first;
	Semester* curSemester = schoolYear->nowSemester;

	int cnt = 0;
	for (Semester* i = schoolYear->nowSemester; i; i = i->nextSemester) {
		cnt++;
	}

	tgui::String curDir = "SchoolYears/"
		+ tgui::String(schoolYear->startYear) + '-' + tgui::String(schoolYear->endYear) + '/';
	curDir += "Semester" + tgui::String(cnt) + "/Courses/";

	int curHeight = 0;
	for (Course* i = curSemester->nowCourse; i; i = i->nextCourse) {
		curHeight++;
		vector<tgui::String> tmp;
		tmp = { tgui::String(i->courseID), tgui::String(i->courseName), tgui::String(i->getFirstSessionDate()), tgui::String(i->getSecondSessionDate()), tgui::String(i->teacherName) };

		for (Student* j = i->nxtStudent; j; j = j->nextStudent) {
			if (j->studentID == neededStudent.studentID) {
				gui.get<Group>("group_registration_result")->get<tgui::ListView>("ListResult")->addItem(tmp);
				break;
			}
		}
	}
}