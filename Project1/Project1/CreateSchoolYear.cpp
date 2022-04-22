#include "CreateSchoolYear.h"
#include "Scoreboard.h"
#include "Student.h"

SpecificClass* Class;
SchoolYear* schoolyear;

void addNewClassToList(SpecificClass*& now)
{
	if (Class == nullptr)
	{
		Class = now;
		Class->nextClass = nullptr;
		return;
	}
	now->nextClass = Class;
	Class = now;
}

void delListClass(SpecificClass*& delClass)
{
	SpecificClass* delptr = delClass;
	delClass = delClass->nextClass;
	delete delptr;
}

void createListOfClasses(Group& group_create)
{
	group_create.get<ListView>("ListClasses")->removeAllColumns();
	group_create.get<ListView>("ListClasses")->removeAllItems();
	group_create.get<ListView>("ListClasses")->addColumn("List of First-Year Classes", 722, ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListClasses")->setVisible(true);
	if (Class == nullptr)
	{
		return;
	}
	int cnt = 0;
	for (SpecificClass* cur = Class; cur; cur = cur->nextClass)
	{
		cnt++;
		group_create.get<ListView>("ListClasses")->addItem(cur->classCODE);
	}
	group_create.get<ListView>("ListClasses")->setSize(725, 25 + 20 * (cnt + 1));
}

void createListView(Group& group_create)
{
	group_create.get<ListView>("ListView1")->setVisible(true);
	group_create.get<ListView>("ListView1")->removeAllColumns();
	group_create.get<ListView>("ListView1")->removeAllItems();
	group_create.get<ListView>("ListView1")->addColumn("No", 40, tgui::ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListView1")->addColumn("StudentID ", 110, tgui::ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListView1")->addColumn("Firt Name", 140, tgui::ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListView1")->addColumn("Last Name", 120, tgui::ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListView1")->addColumn("Gender", 95, tgui::ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListView1")->addColumn("DOB", 121, tgui::ListView::ColumnAlignment::Center);
	group_create.get<ListView>("ListView1")->addColumn("SocialId", 90, tgui::ListView::ColumnAlignment::Center);
	int cnt = 0;
	if (Class == nullptr)
	{
		return;
	}
	for (Student* cur = Class->classStudent; cur; cur = cur->nextStudent)
	{
		;
		cnt++;
		strcpy(cur->specificClass, Class->className);
		tgui::String gender = cur->gender == 0 ? "male" : "female";
		tgui::String dob = tgui::String(cur->DoB.date) + "/" + tgui::String(cur->DoB.month) + "/" + tgui::String(cur->DoB.year);
		group_create.get<ListView>("ListView1")->addItem({ tgui::String(cnt) , tgui::String(cur->studentID) , cur->firstName , cur->lastName , gender , dob , tgui::String(cur->socialID) });
	}
	group_create.get<ListView>("ListView1")->setSize(725, cnt * 25 + 25);
}

bool inputFileFromCSV(string file_path)
{
	if (file_path.find(".csv") == string::npos) return false;
	ifstream fin(file_path);
	string line, word;
	int num = 0;
	SpecificClass* now = new SpecificClass;

	while (getline(fin, line)) {
		num++;
		if (num == 1) {
			//cerr << "Lmao\n";
			continue;
		}
		stringstream str(line);
		int cnt = 0;
		int no = 0, ID = 0, sID = 0, credit = 0;
		bool gen = true;
		DateofBirth dob;
		dob.date = dob.month = dob.year = 0;
		char fName[FULLNAMELENGTH];
		char lName[FULLNAMELENGTH];
		char sClass[FULLNAMELENGTH] = "21CTT1";
		while (getline(str, word, ',')) {
			cnt++;
			stringstream stoint(word);
			switch (cnt) {
			case 1:
				stoint >> no;
				break;
			case 2:
				stoint >> ID;
				//cerr << ID << '\n';
				break;
			case 3:
				for (int i = 0; i < word.length(); i++) {
					fName[i] = word[i];
					//cerr << fName[i];
				}
				fName[word.length()] = '\0';
				//cerr << strlen(fName) << '\n';
				break;
			case 4:
				for (int i = 0; i < word.length(); i++) {
					lName[i] = word[i];
				}
				lName[word.length()] = '\0';
				break;
			case 5:
				stoint >> gen;
				break;
			case 6:
				dob = now->classStudent->getDoB(&word);
				break;
			case 7:
				stoint >> sID;
				now->classStudent->addNewStudent(now->classStudent, new Student(no, ID, fName, lName, gen, dob, sID, sClass, credit));
				break;
			}
		}
	}
	now->nextClass = nullptr;
	addNewClassToList(ref(now));
	fin.close();
	return true;

}

bool okClassName(string classname)
{
	if (Class == nullptr) return true;
	for (SpecificClass* cur = Class; cur; cur = cur->nextClass)
	{
		char nowClassCode[NAMELENGTH];
		strcpy(nowClassCode, classname.c_str());
		if (strcmp(nowClassCode, cur->classCODE) == false)
		{
			return false;
		}
	}
	return true;
}

void onCreateYearSelected(Group& group_create)
{
	group_create.get<Panel>("PanelYear")->setVisible(true);
	group_create.get<ChildWindow>("CourseWindow")->setVisible(false);
	group_create.get<Panel>("PanelSemester")->setVisible(false);
}

void onAddClass(Group& group_create)
{
	string classname = group_create.get<tgui::EditBox>("ClassName")->getText().toStdString();
	if (classname == "")
	{
		group_create.get<Label>("Error")->setVisible(true);
		group_create.get<Label>("Error")->setText("Error : Please enter classname");
		return;
	}
	if (!okClassName(classname.c_str()))
	{
		group_create.get<Label>("Error")->setVisible(true);
		group_create.get<Label>("Error")->setText("Error : Already loaded class");
		return;
	}
	group_create.get<ListView>("ListView1")->setVisible(false);
	group_create.get<Button>("AddClass")->setVisible(false);
	group_create.get<ListView>("ListClasses")->setVisible(true);
	strcpy(Class->classCODE, classname.c_str());
	createListOfClasses(group_create);
}

void onAddSchoolYear(Group& group_create)
{
	schoolyear->nowClass = Class; 
	schoolyear->createNewSchoolYear();
	group_create.get<Label>("Message")->setVisible(true);
	group_create.get<ChildWindow>("MessageWindow")->setVisible(true);
	group_create.get<Label>("Message")->setText("Create School Year " + tgui::String(schoolyear->startYear) + "-" + tgui::String(schoolyear->endYear) + " successfully");
	group_create.get<ChildWindow>("MessageWindow")->moveToFront();
	//roup_create.get<Button>("Reload")->
}

void onLoad(Group& group_create)
{
	string file_path = Get_path();
	int pos = 0;
	for (int i = file_path.size() - 1; i >= 0; i--)
	{
		if (file_path[i] == char(92))
		{
			pos = i;
			break;
		}
	}
	string file_name = file_path.substr(pos + 1);
	group_create.get<Label>("File")->setText(file_name);
	if (inputFileFromCSV(file_path))
	{
		group_create.get<Label>("Error")->setVisible(false);
		group_create.get<Button>("AddClass")->setVisible(true);
		createListView(group_create);
	}
	else {
		group_create.get<Label>("Error")->setText("Error : Unindentified file");
		group_create.get<Label>("Error")->setVisible(true);
	}
	group_create.get<ListView>("ListClasses")->setVisible(false);
}

void init_group_create_year(Group& group_create)
{

	auto group_create_year = tgui::Group::create();
	group_create_year->loadWidgetsFromFile("CreateSchoolYearForm.txt");
	group_create.add(group_create_year->get<Panel>("PanelYear"));
	Class = nullptr;
	ifstream fin("SchoolYears/ListSchoolYear.txt");
	int year;
	while (fin >> year)
	{
	}
	year++;
	schoolyear = new SchoolYear(year, year + 1);
	group_create.get<Label>("NumYear")->setText(tgui::String(year) + "-" + tgui::String(year + 1));
}

void loadcreateYearwidget(Group& group_create)
{
	init_group_create_year(group_create);
	group_create.get<ListView>("ListView1")->setVisible(false);
	group_create.get<Label>("Error")->setVisible(false);
	group_create.get<Label>("Message")->setVisible(false);
	group_create.get<tgui::Button>("Load")->onClick(&onLoad, ref(group_create));
	group_create.get<tgui::Button>("AddClass")->onClick(&onAddClass, ref(group_create));
	group_create.get<tgui::Button>("AddSchoolYear")->onClick(&onAddSchoolYear, ref(group_create));
	createListOfClasses(group_create);
}