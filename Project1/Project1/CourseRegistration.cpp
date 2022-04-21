#include "CourseRegistration.h"

void onCorseRegistrationSelected(tgui::Group& group_registration, tgui::Group& group_student) {
	group_registration.setVisible(true);
	group_student.setVisible(false);
}

bool checkSameSchedule(tgui::Group& group_registration, Course* nowCourse) {
	int cnt1 = 0;
	for (Course* i = nowCourse; i; i = i->nextCourse) {
		cnt1++;
		int cnt2 = 0;
		for (Course* j = nowCourse; j; j = j->nextCourse) {
			cnt2++;
			if (cnt1 == cnt2) continue;

			pair<int, int> a = { i->session1, i->session1Day };
			pair<int, int> b = { j->session2, j->session2Day };

			if (a == b) {
				return false;
			}
		}
	}
	return true;
}

void onButtonSelected(tgui::Group& group_registration, string curDir, Course* nowCourse, Student curStudent) {
	if (!checkSameSchedule(group_registration, nowCourse)) {
		cout << "Not good bro\n";
		return;
	}

	int cntHeight = 0;
	for (Course* i = nowCourse; i; i = i->nextCourse) {
		cntHeight++;
		tgui::String curCheckBox = "CheckBox" + tgui::String(cntHeight);
		
		bool checkViable = false;

		//Student* nxtStudent = nullptr;
		vector<TemporaryData> nxtStudent;

		string line, word;
		int num = 0;

		ifstream fin;
		//cerr << curDir + i->courseName + ".csv" << '\n';
		fin.open(curDir + i->courseName + ".csv");

		while (getline(fin, line)) {
			num++;
			if (num == 1) {
				//cerr << "Lmao\n";
				continue;
			}
			//cerr << line << '\n';
			stringstream str(line);
			int cnt = 0;
			int no = 0, ID = 0;
			int mMark = 0, fMark = 0, oMark = 0, tMark = 0;
			char fName[FULLNAMELENGTH];
			while (getline(str, word, ',')) {
				cnt++;
				stringstream stoint(word);
				switch (cnt) {
				case 1:
					stoint >> no;
					break;
				case 2:
					stoint >> ID;
					//cerr << ID << '\n';
					if (ID == curStudent.studentID) {
						checkViable = true;
					}
					break;
				case 3:
					for (int i = 0; i < word.length(); i++) {
						fName[i] = word[i];
						//cerr << fName[i];
					}
					fName[word.length()] = '\0';
					//cerr << strlen(fName) << '\n';
					break;
				case 4:
					stoint >> mMark;
					break;
				case 5:
					stoint >> fMark;
					break;
				case 6:
					stoint >> oMark;
					break;
				case 7:
					stoint >> tMark;
					break;
				default:
					break;
				}
			}
			nxtStudent.push_back(TemporaryData(no, ID, mMark, fMark, oMark, tMark, fName));
		}
		fin.close();

		fin.open(curDir + i->courseName + ".txt");
		vector<int> ID;

		bool checkViable2 = false;
		while (!fin.eof()) {
			int id;
			fin >> id;
			if (id > 0) ID.push_back(id);
			else continue;

			if (id == curStudent.studentID) {
				checkViable2 = true;
				//cerr << "It's true tho\n";
			}
		}
		fin.close();

		ofstream fout;
		fout.open(curDir + i->courseName + ".csv");

		fout << "No,StudentID,Student Full Name,Midterm Mark";
		fout << ",Final Mark,Other Mark,Total Mark" << endl;

		bool isCheck = group_registration.get<tgui::CheckBox>(curCheckBox.toStdString())->isChecked();

		for (int j = 0; j < nxtStudent.size(); j++) {
			//string fullName = nxtStudent[j].fName;

			if (nxtStudent[j].ID == curStudent.studentID && !isCheck) {
				continue;
			}

			fout << nxtStudent[j].no << "," << nxtStudent[j].ID << "," << nxtStudent[j].fName << "," << nxtStudent[j].mMark << "," << nxtStudent[j].fMark << "," << nxtStudent[j].oMark << "," << nxtStudent[j].tMark << endl;
		}

		string fullName = curStudent.firstName;
		fullName += ' ';
		fullName += curStudent.lastName;
		if (!checkViable && isCheck) {
			fout << curStudent.No << "," << curStudent.studentID << "," << fullName << "," << 0 << "," << 0 << "," << 0 << "," << 0 << endl;
		}
		fout.close();

		fout.open(curDir + i->courseName + ".txt");
		for (int j = 0; j < ID.size(); j++) {
			if (ID[j] == curStudent.studentID && !isCheck) {
				continue;
			}
			if (j > 0 && ID[j] == ID[j - 1]) {
				continue;
			}
			fout << ID[j] << '\n';
		}
		if (!checkViable2 && isCheck) {
			fout << curStudent.studentID << '\n';
		}
		fout.close();
	}
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

		for (Student* j = i->nxtStudent; j; j = j->nextStudent) {
			if (j->studentID == neededStudent.studentID) {
				group_registration.get<tgui::CheckBox>(order.toStdString())->setChecked(true);
			}
		}
	}

	group_registration.get<tgui::Button>("Button1")->onClick(&onButtonSelected, ref(group_registration), curDir.toStdString(), curSemester->nowCourse, neededStudent);
}