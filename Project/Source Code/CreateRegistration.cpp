#include "CreateRegistration.h"
#include "CreateSchoolYear.h"
#include "CreateCourse.h"
#include "CreateSemester.h"
#include "Scoreboard.h"
#include "Student.h"

void init_group_create(Group& group_create)
{
	group_create.loadWidgetsFromFile("CreateForm.txt");
	loadcreateYearwidget(group_create);
	loadcreateSemesterwidget(group_create);
}
void onCreateSelected(Group& group_create, Group& group_student)
{
	group_create.setVisible(true);
	group_student.setVisible(false);
}
void loadcreatewidget(Group& group_create)
{
	init_group_create(group_create);
	group_create.get<Panel>("PanelYear")->setVisible(false);
	group_create.get<ChildWindow>("CourseWindow")->setVisible(false);
	group_create.get<Panel>("PanelSemester")->setVisible(false);
	group_create.get<ChildWindow>("MessageWindow")->setVisible(false);
	group_create.get<Button>("Create School Year")->onClick(&onCreateYearSelected, ref(group_create));
	group_create.get<Button>("Create Semester")->onClick(&onCreateSemesterSelected, ref(group_create));
	group_create.get<Button>("AddCourse")->onClick(&onCreateCourseSelected, ref(group_create));
}