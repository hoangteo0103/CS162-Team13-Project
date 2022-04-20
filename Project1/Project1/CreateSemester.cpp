#include "CreateSemester.h"
#include "direct.h"


Semester* semester = new Semester(Date(0,0,0), Date(0,0,0));

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
bool is_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}
int check_info(Group& group_create, Semester*& semester)
{
	if (group_create.get<ComboBox>("ComboYear")->getSelectedItemIndex() == -1 || group_create.get<ComboBox>("ComboSemester")->getSelectedItemIndex() == -1)
	{
		return 0;
	}
	if (group_create.get<EditBox>("GetStart")->getText() == "" || group_create.get<EditBox>("GetEnd")->getText() == "")
	{
		return 0;
	}
	if (group_create.get<EditBox>("EditBoxStart")->getText() == "" || group_create.get<EditBox>("EditBoxStart")->getText() == "")
	{
		return 0;
	}
	return 1;
}

void create_course_file(Semester*& semester , string year )
{
	ofstream create3("SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses/" + "Courses.csv");
	create3 << "courseID, courseName, teacherName, creadit, maxstudent, session1, session1Day, session2, session2Day" << endl;
	for (Course* cur = semester->nowCourse; cur; cur = cur->nextCourse)
	{
		string name_course = "SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses/" + cur->courseName + " - " + year.substr(0, 4);
		ofstream create(name_course + ".txt");
		create << NULL;
		ofstream create2(name_course + ".csv");
		create2 << "No,StudentID,Student Full Name,Midterm";
		create2 << ",Mark,Final Mark,Other Mark,Total Mark" << endl;	
		create3 << cur->courseID << "," << cur->courseName + string(" - ") + year.substr(0, 4) << "," << cur->teacherName << ",";
		create3 << cur->maximumStudentNum << "," << cur->credits << "," << cur->session1 << "," << cur->session1Day << "," << cur->session2 << "," << cur->session2Day << endl;
	}
}

void onAddSemesterSelected(Group& group_create, Semester*& semester)
{
	string year = group_create.get<ComboBox>("ComboYear")->getSelectedItem().toStdString();
	string file_path = "SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses/" + "ListStudentID.txt";
	cout << year << endl;
	cout << file_path << endl;
	if (is_exist(file_path.c_str()))
	{
		
		group_create.get<Label>("ErrorLabel")->setText("Error : Semester existed");
		group_create.get<Label>("ErrorLabel")->setVisible(true);
		return; 
	}
	int check = check_info(ref(group_create) , ref(semester));
	if (!check)
	{
		group_create.get<Label>("ErrorLabel")->setText("Enter all information"); 
		group_create.get<Label>("ErrorLabel")->setVisible(true);
	}


	_mkdir(("SchoolYears/" + year + "/Semester" + to_string(semester->No)).c_str());
	_mkdir(("SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses").c_str());
	ofstream create("SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses/" + "ListStudentID.txt");
	create << NULL;

	ofstream write("SchoolYears/" + year + "/ListofSemester.txt");
	write << semester->No;

	_mkdir(("SchoolYears/" + year + "/Semester" + to_string(semester->No)).c_str());
	_mkdir(("SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses Registration").c_str());
	ofstream create2("SchoolYears/" + year + "/Semester" + to_string(semester->No) + "/Courses Registration/" + "ListStudentID.txt");
	create2 << NULL;

	create_course_file(ref(semester), year);
	group_create.get<ChildWindow>("MessageWindow")->setVisible(true); 
	group_create.get<ChildWindow>("MessageWindow")->moveToFront();
	group_create.get<Label>("Message")->setVisible(true);
	group_create.get<Label>("Message")->setText("Create Semester " + tgui::String(semester->No) + " year " + year + " successfully");
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
	semester->No = no ;
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
	group_create.get<ComboBox>("ComboSemester")->onItemSelect(&onComboNoSelected, ref(group_create));
	group_create.get<ListView>("ListCourse")->onDoubleClick(&onCourseDoubleClick, ref(group_create), ref(semester));
	group_create.get<Button>("AddSemester")->onClick(&onAddSemesterSelected, ref(group_create), ref(semester)); 
}