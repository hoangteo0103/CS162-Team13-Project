#include "CreateCourse.h"

bool check(Group& group_create)
{
	if (group_create.get<EditBox>("GetID")->getText() == "")
		return false;
	if (group_create.get<EditBox>("GetName")->getText() == "")
		return false;
	if (group_create.get<EditBox>("GetTeacherName")->getText() == "")
		return false;
	if (group_create.get<EditBox>("GetCredit")->getText() == "")
		return false;
	if (group_create.get<EditBox>("GetMax")->getText() == "")
		return false;
	if (group_create.get<ComboBox>("ComboBox1")->getSelectedItemId() == tgui::String(-1))
		return false;
	if (group_create.get<ComboBox>("ComboBox2")->getSelectedItemId() == tgui::String(-1))
		return false;
	bool ok = false;
	for (int i = 0; i <= 3; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i + 1))->isChecked() == true)
			ok = true;
	}
	if (!ok) return false;
	ok = false;
	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i))->isChecked() == true)
			ok = true;
	}
	if (!ok) return false;
	return true;
}
int check_intersect(Group& group_create, Semester*& semester)
{
	int session1, session1day, session2, session2day;
	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i - 1))->isChecked() == true)
		{
			session1 = i;
			break;
		}
	}

	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i))->isChecked() == true)
		{
			session2 = i;
			break;
		}
	}
	session1day = group_create.get<ComboBox>("ComboBox1")->getSelectedItemIndex() + 2;
	session2day = group_create.get<ComboBox>("ComboBox2")->getSelectedItemIndex() + 2;
	pair<int, int > day1 = { session1 , session1day };
	pair<int, int > day2 = { session2 , session2day };
	if (day1 == day2)
	{
		return 0;
	}

	if (!semester->nowCourse)
		return 2;
	for (Course* cur = semester->nowCourse; cur; cur = cur->nextCourse)
	{
		pair<int, int > day1 = { session1 , session1day };
		pair<int, int > day2 = { session2 , session2day };
		pair<int, int > day3 = { cur->session1 , cur->session1Day };
		pair<int, int > day4 = { cur->session2 , cur->session2Day };
		if (day1 == day2)
		{
			return 0;
		}
		if (day1 == day3 || day1 == day4 || day2 == day4 || day2 == day3)
		{
			return 1;
		}
	};
	return 2;
}

int check_intersect2(Group& group_create, Semester*& semester ,Course*& course)
{
	int session1, session1day, session2, session2day;
	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i - 1))->isChecked() == true)
		{
			session1 = i;
			break;
		}
	}

	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i))->isChecked() == true)
		{
			session2 = i;
			break;
		}
	}
	session1day = group_create.get<ComboBox>("ComboBox1")->getSelectedItemIndex() + 2;
	session2day = group_create.get<ComboBox>("ComboBox2")->getSelectedItemIndex() + 2;
	pair<int, int > day1 = { session1 , session1day };
	pair<int, int > day2 = { session2 , session2day };
	if (day1 == day2)
	{
		return 0;
	}

	if (!semester->nowCourse)
		return 2;
	for (Course* &cur = semester->nowCourse; cur; cur = cur->nextCourse)
	{
		pair<int, int > day1 = { session1 , session1day };
		pair<int, int > day2 = { session2 , session2day };
		pair<int, int > day3 = { cur->session1 , cur->session1Day };
		pair<int, int > day4 = { cur->session2 , cur->session2Day };
		if (day1 == day2)
		{
			return 0;
		}
		if (day1 == day3 || day1 == day4 || day2 == day4 || day2 == day3)
		{
			return 1;
		}
	};
	return 2;
}


void createCourseListView(Group& group_create, Semester*& semester)
{
	group_create.get<ListView>("ListCourse")->removeAllColumns();
	group_create.get<ListView>("ListCourse")->removeAllItems();
	group_create.get<ListView>("ListCourse")->addColumn("ID", 30);
	group_create.get<ListView>("ListCourse")->addColumn("Name", 100);
	group_create.get<ListView>("ListCourse")->addColumn("TeacherName", 100);
	group_create.get<ListView>("ListCourse")->addColumn("Credit", 50);
	group_create.get<ListView>("ListCourse")->addColumn("Session1", 100);
	group_create.get<ListView>("ListCourse")->addColumn("Session2", 100);
	group_create.get<ListView>("ListCourse")->addColumn("MaximumStudent", 120);
	if (semester->nowCourse == nullptr)
	{
		group_create.get<ListView>("ListCourse")->setSize(610, 150);
		return; 
	}
	group_create.get<ListView>("ListCourse")->setTextSize(11);

	for (Course* cur = semester->nowCourse; cur ; cur = cur->nextCourse)
	{
		group_create.get<ListView>("ListCourse")->addItem({ tgui::String(cur->courseID), cur->courseName, cur->teacherName, tgui::String(cur->credits), cur->getFirstSessionDate(), cur->getSecondSessionDate(), tgui::String(cur->maximumStudentNum) });
	}
	
}

void LoadModifyCourse(Group& group_create, Course*& cur)
{
	group_create.get<ChildWindow>("CourseWindow")->setVisible(true);
	group_create.get<Label>("ErrorMessage")->setVisible(false);
	group_create.get<Button>("Change")->setVisible(true);
	group_create.get<Button>("Delete")->setVisible(true);
	group_create.get<Button>("AddToList")->setVisible(false);
	group_create.get<EditBox>("GetID")->setText(tgui::String(cur->courseID));
	group_create.get<EditBox>("GetName")->setText(cur->courseName);
	group_create.get<EditBox>("GetTeacherName")->setText(cur->teacherName);
	group_create.get<EditBox>("GetCredit")->setText(tgui::String(cur->credits));
	group_create.get<EditBox>("GetMax")->setText(tgui::String(cur->maximumStudentNum));
	group_create.get<ComboBox>("ComboBox1")->setSelectedItemByIndex(cur->session1Day - 2 );
	group_create.get<ComboBox>("ComboBox2")->setSelectedItemByIndex(cur->session2Day - 2);
	for (int i = 1; i <= 8; i++)
	{
		group_create.get<RadioButton>("RadioButton" + tgui::String(i))->setChecked(false);
	}
	group_create.get<RadioButton>("RadioButton" + tgui::String(2 * cur->session1 - 1))->setChecked(true); 
	group_create.get<RadioButton>("RadioButton" + tgui::String(2 * cur->session2))->setChecked(true); 

}
void onChangeSelected(Group& group_create , Semester*& semester , Course* & course)
{
	if (!check(group_create))
	{
		group_create.get<Label>("ErrorMessage")->setVisible(true);
		group_create.get<Label>("ErrorMessage")->setText("Enter all information");
		return;
	}
	int check = check_intersect(ref(group_create), ref(semester) );
	if (check == 0)
	{
		group_create.get<Label>("ErrorMessage")->setVisible(true);
		group_create.get<Label>("ErrorMessage")->setText("Session 1,2 intersect");
		return;
	}
	if (check == 1)
	{
		group_create.get<Label>("ErrorMessage")->setVisible(true);
		group_create.get<Label>("ErrorMessage")->setText("Session already choosed");
		return;
	}


	int session1, session1day, session2, session2day;
	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i - 1))->isChecked() == true)
		{
			session1 = i;
			break;
		}
	}

	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i))->isChecked() == true)
		{
			session2 = i;
			break;
		}
	}
	session1day = group_create.get<ComboBox>("ComboBox1")->getSelectedItemIndex() + 2;
	session2day = group_create.get<ComboBox>("ComboBox2")->getSelectedItemIndex() + 2;
	int id = atoi(group_create.get<EditBox>("GetID")->getText().toStdString().c_str());
	int credit = atoi(group_create.get<EditBox>("GetCredit")->getText().toStdString().c_str());
	int Max = atoi(group_create.get<EditBox>("GetMax")->getText().toStdString().c_str());
	char courseName[FULLNAMELENGTH];
	char teacherName[FULLNAMELENGTH];
	strcpy(courseName, group_create.get<EditBox>("GetName")->getText().toStdString().c_str());
	strcpy(teacherName, group_create.get<EditBox>("GetTeacherName")->getText().toStdString().c_str());
	course->updateCourseInfo(id, courseName, teacherName, credit, session1, session1day, session2, session2day, Max);
	group_create.get<ChildWindow>("CourseWindow")->setVisible(false);
	createCourseListView(ref(group_create), ref(semester));
}

void onDeleteSelected(Group& group_create, Semester*& semester, Course*& course , int index)
{
	group_create.get<ChildWindow>("CourseWindow")->setVisible(false);
	semester->deleteCourse(ref(semester->nowCourse), course);
	createCourseListView(ref(group_create), ref(semester));

}

void ModifyCourse(Group& group_create, Semester*& semester, int index)
{
	if (!semester->nowCourse)
		return; 
	int cnt = 0;
	for (Course*&cur = semester->nowCourse; cur; cur = cur->nextCourse)
	{
		if (cnt == index)
		{
			LoadModifyCourse(ref(group_create), ref(cur));
			group_create.get<Button>("Delete")->onClick(&onDeleteSelected, ref(group_create), ref(semester), ref(cur), index);
			group_create.get<Button>("Change")->onClick(&onChangeSelected, ref(group_create) ,ref(semester) , ref(cur));
			break; 
		}
		cnt++;
	}
}


void onCreateCourseSelected(Group& group_create )
{
	group_create.get<ChildWindow>("CourseWindow")->setVisible(true);
	group_create.get<Button>("Change")->setVisible(false);
	group_create.get<Button>("Delete")->setVisible(false);
	group_create.get<EditBox>("GetID")->setText("");
	group_create.get<EditBox>("GetName")->setText("");
	group_create.get<EditBox>("GetTeacherName")->setText("");
	group_create.get<EditBox>("GetCredit")->setText("");
	group_create.get<EditBox>("GetMax")->setText("50");
	group_create.get<ComboBox>("ComboBox1")->setSelectedItemByIndex(-1);
	group_create.get<ComboBox>("ComboBox2")->setSelectedItemByIndex(-1);
	for (int i = 1; i <= 8; i++)
	{
		group_create.get<RadioButton>("RadioButton" + tgui::String(i))->setChecked(false);
	}
}


void onAddListSelected(Group& group_create , Semester* &semester)
{
	if(!check(group_create))
	{
		group_create.get<Label>("ErrorMessage")->setVisible(true);
		group_create.get<Label>("ErrorMessage")->setText("Enter all information");
		return; 
	}
	int check = check_intersect(ref(group_create), ref(semester));
	if (check == 0)
	{
		group_create.get<Label>("ErrorMessage")->setVisible(true);
		group_create.get<Label>("ErrorMessage")->setText("Session 1,2 intersect");
		return;
	}
	if (check == 1)
	{
		group_create.get<Label>("ErrorMessage")->setVisible(true);
		group_create.get<Label>("ErrorMessage")->setText("Session already choosed");
		return;
	}

	int session1, session1day, session2, session2day;
	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i - 1))->isChecked() == true)
		{
			session1 = i;
			break;
		}
	}

	for (int i = 1; i <= 4; i++)
	{
		if (group_create.get<RadioButton>("RadioButton" + tgui::String(2 * i))->isChecked() == true)
		{
			session2 = i;
			break;
		}
	}
	session1day = group_create.get<ComboBox>("ComboBox1")->getSelectedItemIndex() + 2;
	session2day = group_create.get<ComboBox>("ComboBox2")->getSelectedItemIndex() + 2;

	int id = atoi(group_create.get<EditBox>("GetID")->getText().toStdString().c_str());
	int credit = atoi(group_create.get<EditBox>("GetCredit")->getText().toStdString().c_str());
	int Max = atoi(group_create.get<EditBox>("GetMax")->getText().toStdString().c_str());
	char courseName[FULLNAMELENGTH];
	char teacherName[FULLNAMELENGTH];
	strcpy(courseName, group_create.get<EditBox>("GetName")->getText().toStdString().c_str());
	strcpy(teacherName, group_create.get<EditBox>("GetTeacherName")->getText().toStdString().c_str());
	Course* course = new Course(id, courseName, teacherName, credit, session1, session1day, session2, session2day, Max);
	if(semester->numCourse < 5)
		semester->addNewCourse(course);
	group_create.get<ChildWindow>("CourseWindow")->setVisible(false);
	createCourseListView(ref(group_create), ref(semester));
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
	group_create.get<Label>("ErrorMessage")->setVisible(false);
	group_create.get<Button>("Change")->setVisible(false);
	group_create.get<Button>("Delete")->setVisible(false);
	group_create.get<Button>("AddToList")->onClick(&onAddListSelected, ref(group_create) , ref(semester));
	createCourseListView(ref(group_create), ref(semester));
}