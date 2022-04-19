#include "CreateCourse.h"


void onCreateCourseSelected(Group& group_create)
{
	group_create.get<ChildWindow>("CourseWindow")->setVisible(true);
}

void onAddListSelected(Group& group_create)
{

}

void init_group_create_course(Group& group_create)
{

	auto group_create_course = tgui::Group::create();
	group_create_course->loadWidgetsFromFile("CreateCourseForm.txt");
	//group_create_course->get<ChildWindow>("CourseWindow")->setTextSize(11);
	group_create.add(group_create_course->get<ChildWindow>("CourseWindow"));
}

void loadcreateCoursewidget(Group& group_create , Semester* & semester)
{
	init_group_create_course(group_create);
	group_create.get<Button>("AddToList")->onClick(&onAddListSelected, ref(group_create));
}