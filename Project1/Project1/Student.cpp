#include <fstream>
#include <iostream>

using namespace std;

#include "Student.h"

void Student::addNewStudent(Student*& curStudent, Student* addStudent)
{
	if (!curStudent) {
		curStudent = addStudent;
		return;
	}
	addStudent->nextStudent = curStudent;
	curStudent = addStudent;
}

Student::Student() {
	this->nextStudent = nullptr;
}

Student::Student(int no, int ID, char fName[], char lName[], bool gen, DateofBirth dob,
                 int sID, char sClass[], int credit) {
    this->No = no;
    this->socialID = ID;
    strcpy_s(this->firstName, fName);
    strcpy_s(this->lastName, lName);
    this->gender = gen;
    this->DoB = dob;
    this->socialID = sID;
    strcpy_s(this->specificClass, sClass);
    this->totalCredits = credit;
}

DateofBirth Student::getDoB(string* dob) {
	DateofBirth ans;
	int i;
	int sum = 0;
	for (i = 0; (i < (*dob).length()) && ((*dob)[i] != '/'); i++) {
		sum *= 10;
		sum += (*dob)[i] - '0';
	}
	ans.date = sum; sum = 0;
	for (++i; (i < (*dob).length()) && ((*dob)[i] != '/'); i++) {
		sum *= 10;
		sum += (*dob)[i] - '0';
	}
	ans.month = sum; sum = 0;
	for (++i; i < (*dob).length(); i++) {
		sum *= 10;
		sum += (*dob)[i] - '0';
	}
	ans.year = sum;
	return ans;
}

void Student::getInfomation(int& no, int& ID, string& fName, string& lName, bool& gen, DateofBirth& dob,
    int& sID, string& sClass, int& credit) {
    no = this->No;
    ID = this->studentID;
    for (int i = 0; i < strlen(this->firstName); i++) {
        fName.push_back(firstName[i]);
    }
    for (int i = 0; i < strlen(this->lastName); i++) {
        lName.push_back(lastName[i]);
    }
    gen = this->gender;
    dob = this->DoB;
    sID = this->socialID;
    for (int i = 0; i < strlen(this->lastName); i++) {
        sClass.push_back(lastName[i]);
    }
    credit = this->totalCredits;
}

void Student::modifyStudentInfo(int no, int ID, char fName[], char lName[], bool gen, DateofBirth dob,
                 int sID, char sClass[], int credit)
{
    this->No = no;
    this->studentID = ID;
    strcpy_s(this->firstName, fName);
    strcpy_s(this->lastName, lName);
    this->gender = gender;
    this->DoB = dob;
    this->socialID = sID;
    strcpy_s(this->specificClass, sClass);
    this->totalCredits = credit;
    this->nextStudent = nullptr;
}

void Student::inputFileStudentInfo(ifstream &fin)
{
	
}

void Student::outputScreenInfo()
{
	cout << this->No << ' ' << this->studentID << ' ' << this->firstName << ' ' << this->lastName << ' ' << this->gender << endl;
}

void limitCoursesCanEnroll()
{

}

void enrollCourse()
{

}

void SpecificClass::changeClassCode(char classCode[])
{
	strcpy_s(this->classCODE, classCode);
}

void SpecificClass::inputFileClassInfo(string year)
{
	//cerr << "SchoolYears/" + year + this->classCODE + ".csv" << '\n';
	ifstream fin ("SchoolYears/" + year + "/" + this->classCODE + ".csv");

    string line, word;
	int num = 0;

	while (getline(fin, line)) {
		num++;
		if (num == 1) {
			//cerr << "Lmao\n";
			continue;
		}
		//cerr << line << '\n';
		stringstream str(line);
		int cnt = 0;
		int no = 0 , ID = 0 , sID = 0 , credit = 0;
		bool gen = true ;
		DateofBirth dob;
		dob.date = dob.month = dob.year = 0;
		char fName[FULLNAMELENGTH];
		char lName[FULLNAMELENGTH];
		char sClass[FULLNAMELENGTH];
		while (getline(str, word, ',')) {
			cnt++;
            stringstream stoint(word);
			switch (cnt) {
			case 1:
				stoint >> no;
				break;
			case 2:
				stoint >> ID;
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
				dob = this->classStudent->getDoB(&word);
				break;
			case 7:
				stoint >> sID;
				break;
			case 8:
				for (int i = 0; i < word.length(); i++) {
					sClass[i] = word[i];
				}
				sClass[word.length()] = '\0';
				break;
			case 9:
				stoint >> credit;
                break;
			default:
				break;
			}
		}
		//cerr << no << ' ' << ID << ' ' << sID << ' ' << credit << '\n';
		//cerr << fName << ' ' << lName << '\n';
		//cerr << gen << '\n';
		//cerr << dob.date << ' ' << dob.month << ' ' << dob.year << '\n';
		this->classStudent->addNewStudent(this->classStudent, new Student(no, ID, fName, lName, gen, dob, sID, sClass, credit));
		//cerr << (this->classStudent == nullptr) << '\n';
	}
    fin.close();
}

void SpecificClass::outputToScreenClassInfo()
{
	cout << this->classCODE << endl; 
	//cerr << (this->classStudent == nullptr) << '\n';
	for (Student* cur = this->classStudent; cur != nullptr; cur = cur->nextStudent)
	{
		//cerr << "Lmao\n";
		cur->outputScreenInfo();
	}
}
