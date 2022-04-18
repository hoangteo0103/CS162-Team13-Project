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
}