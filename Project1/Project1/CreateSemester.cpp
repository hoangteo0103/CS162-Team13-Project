#include "CreateSemester.h"


Semester* semester = new Semester(Date(0,0,0), Date(0,0,0));
int index = -1;

void onCourseDoubleClick(Group& group_create , Semester* &semester)
{
	int id = group_create.get<tgui::ListView>("ListCourse")->getSelectedItemIndex();
	if (semester->nowCourse == nullptr)
	{
		return;
	}
	ModifyCourse(ref(group_create), ref(semester), id);
	
}


void onCreateSemesterSelected(Group& group_create)
{
	group_create.get<Panel>("PanelYear")->setVisible(false);
	group_create.get<ChildWindow>("CourseWindow")->setVisible(false);
	group_create.get<Panel>("PanelSemester")->setVisible(true);
}

void onComboYearSelected(Group& group_create)
{
	string selectedItem = group_create.get<ComboBox>("ComboYear")->getSelectedItem().toStdString();
	int year = atoi(selectedItem.substr(0, 4).c_str());
	semester->startSchoolYear = year; 
	semester->endSchoolYear = year + 1;
}

void onComboNoSelected(Group& group_create)
{
	string selectedItem = group_create.get<ComboBox>("ComboSemester")->getSelectedItem().toStdString();
	int no = atoi(selectedItem.c_str());
	semester->No = no;
}


void init_group_create_semester(Group& group_create)
{

	auto group_create_semester = tgui::Group::create();
	group_create_semester->loadWidgetsFromFile("CreateSemesterForm.txt");
	group_create.add(group_create_semester->get<Panel>("PanelSemester"));
	group_create.get<Label>("StartDate")->setTextSize(11);
	group_create.get<Label>("EndDate")->setTextSize(11);
	ifstream fin("SchoolYears/ListSchoolYear.txt");
	int year;
	while (fin >> year)
	{
		group_create.get<ComboBox>("ComboYear")->addItem(tgui::String(year) + "-" + tgui::String(year+1));
	}
}

void loadcreateSemesterwidget(Group& group_create)
{
	init_group_create_semester(group_create);
	loadcreateCoursewidget(group_create , ref(semester));
	group_create.get<ComboBox>("ComboYear")->onItemSelect(&onComboYearSelected, ref(group_create));
	group_create.get<ListView>("ListCourse")->onDoubleClick(&onCourseDoubleClick, ref(group_create), ref(semester));
}