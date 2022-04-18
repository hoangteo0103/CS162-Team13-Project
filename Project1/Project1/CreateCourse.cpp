#include "CreateCourse.h"
#include "CreateSchoolYear.h"
#include "Scoreboard.h"
#include "Student.h"

void onCreateCourseSelected(Group& group_create)
{
	group_create.get<Panel>("PanelYear")->setVisible(false);
	group_create.get<Panel>("PanelCourse")->setVisible(true);
}
void init_group_create_course(Group& group_create)
{

	auto group_create_course = tgui::Group::create();
	group_create_course->loadWidgetsFromFile("CreateCourseForm.txt");
	group_create.add(group_create_course->get<Panel>("PanelCourse"));
	group_create.get<Label>("StartDate")->setTextSize(11);
	group_create.get<Label>("EndDate")->setTextSize(11);
	ifstream fin("SchoolYears/ListSchoolYear.txt");
	int year;
	while (fin >> year)
	{
		group_create.get<ComboBox>("ComboYear")->addItem(tgui::String(year) + "-" + tgui::String(year + 1));
	}
}

void loadcreateCoursewidget(Group& group_create)
{
	init_group_create_course(group_create);
}