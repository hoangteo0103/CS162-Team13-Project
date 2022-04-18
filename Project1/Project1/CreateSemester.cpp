#include "CreateSemester.h"
#include "CreateSchoolYear.h"
#include "Scoreboard.h"
#include "Student.h"

void onCreateSemesterSelected(Group& group_create)
{
	group_create.get<Panel>("PanelYear")->setVisible(false);
	group_create.get<Panel>("PanelSemester")->setVisible(true);
}
void init_group_create_semester(Group& group_create)
{

	auto group_create_semester = tgui::Group::create();
	group_create_semester->loadWidgetsFromFile("CreateSemesterForm.txt");
	group_create.add(group_create_semester->get<Panel>("PanelSemester"));
	//Class = nullptr;
	ifstream fin("SchoolYears/ListSchoolYear.txt");
	int year;
	while (fin >> year)
	{
	}
	year++;
	//schoolyear = new SchoolYear(year, year + 1);
	//group_create.get<Label>("NumYear")->setText(tgui::String(year) + "-" + tgui::String(year + 1));
}

void loadcreateSemesterwidget(Group& group_create)
{
	init_group_create_semester(group_create);
}