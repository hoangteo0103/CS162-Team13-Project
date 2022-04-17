#include "TeacherStudentInfo.h"

map <tgui::String, vector<vector<tgui::String>>> mpInfo;

void init_student_info(Group& group_studentInfo) {
	group_studentInfo.loadWidgetsFromFile("TeacherStudentInfoForm.txt");
}

void onItemDoubleClick(Group& group_studentInfo, Group& group_small_studentInfo, SchoolYear* curSchoolYear) {
	int target = group_studentInfo.get<tgui::ListView>("ListView1")->getSelectedItemIndex();
	vector<tgui::String> tmp = group_studentInfo.get<tgui::ListView>("ListView1")->getItemRow(target);

	for (SchoolYear* i = curSchoolYear; i; i = i->nextSchoolYear) {
		for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
			//cerr << j->classCODE << '\n';
			for (Student* k = j->classStudent; k != nullptr; k = k->nextStudent) {
				string name1 = tmp[2].toStdString();
				string name2 = k->firstName;
				name2 += ' ';
				name2 += k->lastName;
				if (!name1.compare(name2)) {
					loadInfoWidget(group_small_studentInfo, *k);
					onStudentInfoSelected(group_small_studentInfo, group_studentInfo);
					return;
				}
 			}
		}
	}
}

void onComboBoxesSelected(Group& group_studentInfo, tgui::String getSelectedItem) {
	if (getSelectedItem == "All Semesters")
	{
		group_studentInfo.get<tgui::ListView>("ListView1")->removeAllItems();
		int width = 0;
		for (auto t : mpInfo)
		{
			//cout << t.second.size() << endl;
			width += t.second.size();
			group_studentInfo.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

		}
		group_studentInfo.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 600LL));

	}
	else {
		group_studentInfo.get<tgui::ListView>("ListView1")->setSize(1100, 50);
		group_studentInfo.get<tgui::ListView>("ListView1")->removeAllItems();
		group_studentInfo.get<tgui::ListView>("ListView1")->addMultipleItems(mpInfo[getSelectedItem]);
		group_studentInfo.get<tgui::ListView>("ListView1")->setSize(1100, min(50LL * long long(mpInfo[getSelectedItem].size()) + 80, 600LL));

	}
}

void loadStudentWidget(Group& group_studentInfo, SchoolYear*& curSchoolYear) {
	init_student_info(group_studentInfo);

	group_studentInfo.get<tgui::ListView>("ListView1")->addColumn("Class", 100, tgui::ListView::ColumnAlignment::Center);
	group_studentInfo.get<tgui::ListView>("ListView1")->addColumn("Student ID", 200, tgui::ListView::ColumnAlignment::Center);
	group_studentInfo.get<tgui::ListView>("ListView1")->addColumn("Student's Name", 700);

	group_studentInfo.get<tgui::ComboBox>("ComboBox1")->addItem("All Semesters");
	group_studentInfo.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("All Semesters");

	for (SchoolYear* i = curSchoolYear; i; i = i->nextSchoolYear) {
		//cerr << i->startYear << ' ' << i->endYear << '\n';
		for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
			group_studentInfo.get<tgui::ComboBox>("ComboBox1")->addItem(tgui::String(j->classCODE));

			vector<tgui::String> tmp;
			for (Student* k = j->classStudent; k; k = k->nextStudent) {
				tgui::String name = k->firstName;
				name += ' ';
				name += k->lastName;

				tmp = { tgui::String(j->classCODE), tgui::String(k->studentID), name };
				mpInfo[tgui::String(j->classCODE)].push_back(tmp);
				group_studentInfo.get<tgui::ListView>("ListView1")->addItem(tmp);
			}
		}
	}

	group_studentInfo.get<tgui::ComboBox>("ComboBox1")->onItemSelect(&onComboBoxesSelected, ref(group_studentInfo));
	//group_studentInfo.get<tgui::ListView>("ListView1")->onDoubleClick(&onItemDoubleClick, ref(group_studentInfo), ref(curSchoolYear));
}