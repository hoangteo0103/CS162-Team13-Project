#include "CreateRegistration.h"
#include "Scoreboard.h"
#include "Student.h"

SpecificClass* Class = new SpecificClass ;
SpecificClass* nowClass ;

void addNewClassToList(SpecificClass*& curClass , SpecificClass* &now)
{
	if (curClass->classStudent == nullptr)
	{
		curClass = now; 
		return; 
	}
	now->nextClass = curClass;
	curClass = now; 
}

void delListClass(SpecificClass* &delClass)
{
	Student* student = delClass->classStudent;
	if (student == nullptr) return; 
	while (student->nextStudent)
	{
		Student* delptr = student->nextStudent;
		student->nextStudent = delptr->nextStudent;
		delete delptr;
	}
	delete student;
	delClass->classStudent = nullptr;
}

void createListOfClasses(Group& group_create)
{
	group_create.get<ListView>("ListClasses")->removeAllColumns();
	group_create.get<ListView>("ListClasses")->addColumn("List of First-Year Classes" , 570 , ListView::ColumnAlignment::Center);
	if (Class->classStudent == nullptr)
	{
		group_create.get<ListView>("ListClasses")->addItem("None");
		return;
	}
	for (SpecificClass* cur = Class; cur; cur = cur->nextClass)
	{
		cout << 1;
		group_create.get<ListView>("ListClasses")->addItem(cur->className);
	}
}

void createListView(Group& group_create)
{
	group_create.get<ListView>("ListView1")->setVisible(true);
	group_create.get<ListView>("ListView1")->removeAllColumns();
	group_create.get<ListView>("ListView1")->removeAllItems();
	group_create.get<ListView>("ListView1")->addColumn("No", 30);
	group_create.get<ListView>("ListView1")->addColumn("StudentID ", 90);
	group_create.get<ListView>("ListView1")->addColumn("Firt Name", 100);
	group_create.get<ListView>("ListView1")->addColumn("Last Name", 100);
	group_create.get<ListView>("ListView1")->addColumn("Gender", 70);
	group_create.get<ListView>("ListView1")->addColumn("DOB", 100);
	group_create.get<ListView>("ListView1")->addColumn("SocialId", 80);
	int cnt = 0; 
	for (Student* cur = nowClass->classStudent; cur; cur = cur->nextStudent)
	{
		cout << cur->firstName << endl;
		cnt++; 
		tgui::String gender  = cur->gender == 0 ? "male" : "female";
		tgui::String dob = tgui::String(cur->DoB.date) + "/" + tgui::String(cur->DoB.month) + "/" + tgui::String(cur->DoB.year);
		group_create.get<ListView>("ListView1")->addItem({ tgui::String(cnt) , tgui::String(cur->studentID) , cur->firstName , cur->lastName , gender , dob , tgui::String(cur->socialID) });
	}
	group_create.get<ListView>("ListView1")->setSize(570, cnt * 25 + 25);
}

void change(SpecificClass* now, SpecificClass*& nowClass)
{
	nowClass = now;
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
	change(now, nowClass);
	fin.close();
	return true;
	
}

void onCreateSelected(Group& group_create, Group& group_student)
{
	group_create.setVisible(true);
	group_student.setVisible(false);
}
void onAddClass(Group& group_create)
{
	group_create.get<ListView>("ListView1")->setVisible(false); 
	group_create.get<Button>("AddClass")->setVisible(false); 
	group_create.get<ListView>("ListClasses")->setVisible(true);
	string classname =group_create.get<tgui::EditBox>("ClassName")->getText().toStdString();
	strcpy(nowClass->className , classname.c_str());
	addNewClassToList(Class, nowClass);
	createListOfClasses(group_create);
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
		group_create.get<Label>("Error")->setVisible(true);
	}
	group_create.get<ListView>("ListClasses")->setVisible(false);
}

void init_group_create(Group& group_create)
{
	group_create.loadWidgetsFromFile("CreateForm.txt");
	Class->classStudent = nullptr;
	Class->nextClass = nullptr;
}

void loadcreatewidget(Group& group_create)
{
	init_group_create(group_create);
	group_create.get<ListView>("ListView1")->setVisible(false);
	group_create.get<Label>("Error")->setVisible(false);
	group_create.get<tgui::Button>("Load")->onClick(&onLoad, ref(group_create));
	group_create.get<tgui::Button>("AddClass")->onClick(&onAddClass , ref(group_create));
	createListOfClasses(group_create);

}