#include "CreateRegistration.h"
#include "Scoreboard.h"
#include "Student.h"

//SpecificClass inputFileFromCSV(string file_path)
//{
//	SpecificClass* Class = new SpecificClass;
//	ifstream fin(file_path);
//
//	string line, word;
//	int num = 0;
//
//	while (getline(fin, line)) {
//		num++;
//		if (num == 1) {
//			//cerr << "Lmao\n";
//			continue;
//		}
//		//cerr << line << '\n';
//		stringstream str(line);
//		int cnt = 0;
//		int no = 0, ID = 0, sID = 0, credit = 0;
//		bool gen = true;
//		DateofBirth dob;
//		dob.date = dob.month = dob.year = 0;
//		char fName[FULLNAMELENGTH];
//		char lName[FULLNAMELENGTH];
//		char sClass[FULLNAMELENGTH];
//		while (getline(str, word, ',')) {
//			cnt++;
//			stringstream stoint(word);
//			switch (cnt) {
//			case 1:
//				stoint >> no;
//				break;
//			case 2:
//				stoint >> ID;
//				//cerr << ID << '\n';
//				break;
//			case 3:
//				for (int i = 0; i < word.length(); i++) {
//					fName[i] = word[i];
//					//cerr << fName[i];
//				}
//				fName[word.length()] = '\0';
//				//cerr << strlen(fName) << '\n';
//				break;
//			case 4:
//				for (int i = 0; i < word.length(); i++) {
//					lName[i] = word[i];
//				}
//				lName[word.length()] = '\0';
//				break;
//			case 5:
//				stoint >> gen;
//				break;
//			case 6:
//				dob = this->classStudent->getDoB(&word);
//				break;
//			case 7:
//				stoint >> sID;
//				break;
//				Class->addNewStudent(this->classStudent, new Student(no, ID, fName, lName, gen, dob, sID, sClass, credit));
//			}
//			fin.close();
//		}
//	}
//}

void onCreateSelected(Group& group_create, Group& group_student)
{
    group_create.setVisible(true);
    group_student.setVisible(false);
}

void onLoad(Group& group_create)
{
    string file_path = Get_path(); 
    int pos = 0 ; 
    for (int i = file_path.size() - 1; i >= 0; i--)
    {
        if (file_path[i] == ':')
            pos = i;
    }
    file_path = file_path.substr(pos + 2);
    group_create.get<Label>("File")->setText(file_path);
}

void init_group_create(Group& group_create)
{
    group_create.loadWidgetsFromFile("CreateForm.txt");
}
void loadcreatewidget(Group& group_create)
{
    init_group_create(group_create);
    group_create.get<tgui::Button>("Load")->onClick(&onLoad , ref(group_create));
    group_create.get<ListView>("ListView1")->addColumn("No", 30); 
    group_create.get<ListView>("ListView1")->addColumn("StudentID ", 90); 
    group_create.get<ListView>("ListView1")->addColumn("Firt Name", 100);
    group_create.get<ListView>("ListView1")->addColumn("Last Name", 100);
    group_create.get<ListView>("ListView1")->addColumn("Gender", 70);
    group_create.get<ListView>("ListView1")->addColumn("DOB", 80);
    group_create.get<ListView>("ListView1")->addColumn("SocialId", 80);

}