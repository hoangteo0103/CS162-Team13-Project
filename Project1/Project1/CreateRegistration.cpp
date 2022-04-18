#include "CreateRegistration.h"
#include "CreateSchoolYear.h"
#include "Scoreboard.h"
#include "Student.h"

void init_group_create(Group& group_create)
{
	group_create.loadWidgetsFromFile("CreateForm.txt");
	loadcreateYearwidget(group_create);
}
void onCreateSelected(Group& group_create, Group& group_student)
{
	group_create.setVisible(true);
	group_student.setVisible(false);
}
void loadcreatewidget(Group& group_create)
{
	init_group_create(group_create);
	group_create.get<Panel>("PanelYear")->setVisible(true);
}