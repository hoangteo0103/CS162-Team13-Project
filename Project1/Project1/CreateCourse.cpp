#include "CreateCourse.h"
#include "CreateSchoolYear.h"
#include "Scoreboard.h"
#include "Student.h"

void onCreateCourseSelected(Group& group_create)
{
	group_create.get<ChildWindow>("CourseWindow")->setVisible(true);
}
void init_group_create_course(Group& group_create)
{

	auto group_create_course = tgui::Group::create();
	group_create_course->loadWidgetsFromFile("CreateCourseForm.txt");
	group_create.add(group_create_course->get<ChildWindow>("CourseWindow"));
}

void loadcreateCoursewidget(Group& group_create)
{
	init_group_create_course(group_create);
}