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
	this->nextID = nullptr;
}

Course::Course(int ID, char cName[], char tName[], int credit, int ss1, int ss1Day, int ss2, int ss2Day, int mStudent) {
	this->courseID = ID;
	strcpy_s(this->courseName, cName);
	strcpy_s(this->teacherName, tName);
	this->credits = credit;
	this->session1 = ss1;
	this->session1Day = ss1Day;
	this->session2 = ss2;
	this->session2Day = ss2Day;
	if (mStudent > 0) {
		this->maximumStudentNum = mStudent;
	}
	this->nextID = nullptr;
}

void Course::addNewStudent(IDNode* student) {
	if (!this->nextID) {
		nextID = student;
		return;
	}
	student->nextNode = this->nextID;
	this->nextID = student;
}

void Course::delListStudent() {
	if (!this->nextID) return;
	while (this->nextID->nextNode) {
		IDNode* tmp = this->nextID->nextNode;
		this->nextID = tmp->nextNode;
		delete tmp;
	}
	delete this->nextID;
}

void Course::inputFileClassInfo(string curDir) {
	ifstream fin(curDir + "ListStudentID.txt");
	int ID;
	while (fin >> ID) {
		IDNode* nNode = new IDNode;
		nNode->nextNode = nullptr;
		nNode->sID = ID;
		addNewStudent(nNode);
	}
	fin.close();
}

void Course::updateCourseInfo(int ID, char cName[], char tName[], int credit, int ss1, int ss1Day, int ss2, int ss2Day, int mStudent) {
	this->courseID = ID;
	strcpy_s(this->courseName, cName);
	strcpy_s(this->teacherName, tName);
	this->credits = credit;
	this->session1 = ss1;
	this->session1Day = ss1Day;
	this->session2 = ss2;
	this->session2Day = ss2Day;
	if (mStudent > 0) {
		this->maximumStudentNum = mStudent;
	}
}

void Course::outputToScreenClassInfo() {

}

void Course::exportStudentList(fstream& fout) {
	/*for (Student* i = this->classStudents; i; i = i->nextStudent) {
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
	}*/
}

string Course::getFirstSessionDate() {
	string ans = "";
	switch (this->session1) {
	case 1:
		ans += "7:30 ";
		break;
	case 2:
		ans += "9:30 ";
		break;
	case 3:
		ans += "13:30 ";
		break;
	case 4:
		ans += "15:30 ";
		break;
	default:
		break;
	}

	switch (this->session1Day) {
	case 2:
		ans += "Monday";
		break;
	case 3:
		ans += "Tuesday";
		break;
	case 4:
		ans += "Wednesday";
		break;
	case 5:
		ans += "Thursday";
		break;
	case 6:
		ans += "Friday";
		break;
	case 7:
		ans += "Saturday";
		break;
	default:
		break;
	}

	return ans;
}

string Course::getSecondSessionDate() {
	string ans = "";
	switch (this->session2) {
	case 1:
		ans += "7:30 ";
		break;
	case 2:
		ans += "9:30 ";
		break;
	case 3:
		ans += "13:30 ";
		break;
	case 4:
		ans += "15:30 ";
		break;
	default:
		break;
	}

	switch (this->session2Day) {
	case 2:
		ans += "Monday";
		break;
	case 3:
		ans += "Tuesday";
		break;
	case 4:
		ans += "Wednesday";
		break;
	case 5:
		ans += "Thursday";
		break;
	case 6:
		ans += "Friday";
		break;
	case 7:
		ans += "Saturday";
		break;
	default:
		break;
	}

	return ans;
}

bool Course::findStudent(string curDir, string studentID) {
	ifstream fin;
	//std::cerr << curDir + this->courseName + ".txt" << '\n';
	fin.open(curDir + this->courseName + ".txt");
	long val = 0;
	for (int i = 0; i < studentID.length(); i++) {
		val *= 10;
		val += studentID[i] - '0';
	}
	bool check = false;
	while (!fin.eof()) {
		int num;
		fin >> num;
		check = check || (num == val);
	}
	fin.close();

	return check;
}

void importScoreBoard();
void viewScourBoard();
void updateResult();