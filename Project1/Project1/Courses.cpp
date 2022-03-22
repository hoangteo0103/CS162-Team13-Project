#include <fstream>

using namespace std;

#include "Courses.h"

int Course::strToNum(string* num) {
	int ans = 0, l = (*num).length();
	for (int i = 0; i < l; i++) {
		ans *= 10;
		ans += (*num)[i] - '0';
	}
	return ans;
}

DateofBirth Course::getDoB(string* dob) {
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

Course::Course() {
	this->classStudents = nullptr;
}

Course::Course(int ID, char cName[], char tName[], int credit, int ss1, int ss2, int mStudent) {
	this->courseID = ID;
	strcpy_s(this->courseName, cName);
	strcpy_s(this->teacherName, tName);
	this->credits = credit;
	this->session1 = ss1;
	this->session2 = ss2;
	if (mStudent > 0) {
		this->maximumStudentNum = mStudent;
	}
	this->classStudents = nullptr;
}

void Course::addNewStudent(Student* student) {
	if (!this->classStudents) {
		classStudents = student;
		return;
	}
	student->nextStudent = this->classStudents->nextStudent;
	this->classStudents->nextStudent = student;
}

void Course::delListStudent() {
	if (!this->classStudents) return;
	while (this->classStudents->nextStudent) {
		Student* tmp = this->classStudents->nextStudent;
		this->classStudents->nextStudent = tmp->nextStudent;
		delete tmp;
	}
	delete this->classStudents;
}

void Course::inputFileClassInfo() {
	fstream fin;
	fin.open("Students.csv", ios::in);

	string line, word;

	while (getline(fin, line)) {
		stringstream str(line);

		int cnt = 0;
		int no, ID, sID, credit;
		bool gen;
		DateofBirth dob;
		char fName[NAMELENGTH];
		char lName[NAMELENGTH];
		char sClass[NAMELENGTH];
		while (getline(str, word, ',')) {
			cnt++;
			switch (cnt) {
			case 1:
				no = this->strToNum(&word);
				break;
			case 2:
				ID = this->strToNum(&word);
				break;
			case 3:
				for (int i = 0; i < word.length(); i++) {
					fName[i] = word[i];
				}
				fName[word.length()] = '\0';
				break;
			case 4:
				for (int i = 0; i < word.length(); i++) {
					lName[i] = word[i];
				}
				lName[word.length()] = '\0';
				break;
			case 5:
				gen = strToNum(&word);
				break;
			case 6:
				dob = this->getDoB(&word);
				break;
			case 7:
				sID = this->strToNum(&word);
				break;
			case 8:
				for (int i = 0; i < word.length(); i++) {
					sClass[i] = word[i];
				}
				sClass[word.length()] = '\0';
				break;
			case 9:
				credit = this->strToNum(&word);
			default:
				break;
			}

			Student* student = new Student(no, ID, fName, lName, gen, dob, sID, sClass, credit);
			this->addNewStudent(student);
		}
	}
}

void Course::updateCourseInfo(int ID, char cName[], char tName[], int credit, int ss1, int ss2, int mStudent) {
	this->courseID = ID;
	strcpy_s(this->courseName, cName);
	strcpy_s(this->teacherName, tName);
	this->credits = credit;
	this->session1 = ss1;
	this->session2 = ss2;
	if (mStudent > 0) {
		this->maximumStudentNum = mStudent;
	}
}

void Course::outputToScreenClassInfo() {

}

void Course::exportStudentList(fstream& fout) {
	for (Student* i = this->classStudents; i; i = i->nextStudent) {
		int no, ID, sID, credit;
		bool gen;
		DateofBirth dob;
		string fName = "", lName = "", sClass = "";
		i->getInfomation(no, ID, fName, lName, gen, dob, sID, sClass, credit);
		
		fout << no << ',';
		fout << ID << ',';
		fout << fName << ',';
		fout << lName << ',';
		fout << gen << ',';
		fout << dob.date << '/' << dob.month << '/' << dob.year << ',';
		fout << sID << ',';
		fout << sClass << ',';
		fout << credit << '\n';
	}
}

void importScoreBoard();
void viewScourBoard();
void updateResult();