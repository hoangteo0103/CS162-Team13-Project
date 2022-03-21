#include <fstream>
#include <iostream>

using namespace std;

#include "Student.h"

void Student::addNewStudent(Student* addStudent)
{
    Student* curStudent = this;
    while (curStudent != nullptr)
        curStudent = curStudent->nextStudent;
    curStudent = addStudent;
}

Student::Student() {
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

void SpecificClass::changeClassCode(char* classCode)
{
	strcpy_s(this->classCODE, classCode);
}

void SpecificClass::inputFileClassInfo()
{
	 ifstream fin ("SchoolYears/Year2021-2022/SpecificClasses/21CTT1.csv");
    Student* curStudent = classStudent;

    string line, word;
	int num = 0;

	while (getline(fin, line)) {
		stringstream str(line);
		num++; 
		int cnt = 0;
		int no = 0 , ID = 0 , sID = 0 , credit = 0;
		bool gen = true ;
		DateofBirth dob;
		dob.date = dob.month = dob.year = 0;
		char fName[NAMELENGTH];
		char lName[NAMELENGTH];
		char sClass[NAMELENGTH];
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
				}
				break;
			case 4:
				for (int i = 0; i < word.length(); i++) {
					lName[i] = word[i];
				}
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
				break;
			case 9:
				stoint >> credit;
                break;
			default:
				break;
			}
			if (num != 1)
			{
				Student* addStudent = new Student(no, ID, fName, lName, gen, dob, sID, sClass, credit);
				this->classStudent->addNewStudent(addStudent);
			}
		}
	}
    fin.close();
}

void SpecificClass::outputToScreenClassInfo()
{
	cout << this->classCODE << endl; 
	for (Student* cur = this->classStudent; cur != NULL; cur = cur->nextStudent)
	{
		cur->outputScreenInfo();
	}
}
