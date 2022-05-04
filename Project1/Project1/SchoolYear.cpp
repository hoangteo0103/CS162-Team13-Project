#include "SchoolYear.h"
#include "direct.h"
#include <Windows.h>
using namespace std;
SchoolYear::SchoolYear(int startYear, int endYear)
{
	this->startYear = startYear;
	this->endYear = endYear;
	this->nowSemester = nullptr; 
	this->nowClass = nullptr;
}

void copyfile(string source_filename, string dest_filename)
{
	std::ifstream  src(source_filename, std::ios::binary);
	std::ofstream  dst(dest_filename, std::ios::binary);
	dst << src.rdbuf();
}
string GetLastWinError()
{
	LPVOID lpMsgBuf = 0;
	LPVOID lpDisplayBuf = 0;
	DWORD dw = GetLastError();

	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf,
		0, NULL);

	std::ostringstream oss;
	oss << "Windows Error ";
	oss << dw << " :" << (LPCSTR)lpMsgBuf;

	LocalFree(lpMsgBuf);

	return oss.str();

}
string vinh1 = "C:/Work/CS162/Group_Project/Project1/Project1/SchoolYears/";
string hoang1 = "D:/Project - CS162/Project1/Project1/SchoolYears/";
string hao1 = "D:/Visual Studio 2022/Final Project/CS162-Team13-Project/Project1/Project1/SchoolYears/";
string hao2 = "E:/Study/CS162/FinalProject/Project1/Project1/SchoolYears/";
bool SchoolYear::createNewSchoolYear()
{
	string year = hao2 + to_string(this->startYear) + "-" + to_string(this->endYear);
	string previous_year = hao2 + to_string(this->startYear - 1) + "-" + to_string(this->endYear - 1);
	cout << year.c_str();
	if (CreateDirectoryA(year.c_str(), 0))
	{

	}
	else {
		cout << GetLastWinError() << endl;
	}
	ofstream fout(hao2 + "ListSchoolYear.txt", ios_base::app | ios_base::out);
	fout << endl <<this->startYear;
	ofstream f1(year + "/ListOfClassCode.txt");
	ofstream f2(year + "/ListOfSemester.txt");
	string null = "";
	f1 << null;
	f2 << 0;
	copyfile(previous_year +"/ListOfClassCode.txt" , year + "/ListOfClassCode.txt");
	ifstream fin_class(previous_year + "/ListOfClassCode.txt");
	string class_code; 
	while (fin_class >> class_code)
	{
		string ext = "/" + class_code + ".csv"; 
		ofstream f_create(year + ext);
		f_create << null;
		copyfile(previous_year + ext, year + ext);
	}
	ofstream fout1(year + "/ListOfClassCode.txt", ios_base::app | ios_base::out);
	for (SpecificClass* cur = this->nowClass; cur; cur = cur->nextClass)
	{
		string ext = "/" + string(cur->classCODE) + ".csv";
		ofstream f_create(year + ext);
		f_create << "No,Student ID,First Name,Last Name,Gender,Date of Birth,Social ID,Class,Credit" << endl;
		int cnt = 0;
		for (Student* curStudent = cur->classStudent; curStudent; curStudent = curStudent->nextStudent)
		{
			cnt++; 
			string dob = to_string(curStudent->DoB.date) + "/" + to_string(curStudent->DoB.month) + "/" + to_string(curStudent->DoB.year);
			f_create << cnt << ',' << curStudent->studentID << ',' << curStudent->firstName << ',' << curStudent->lastName << ',' << curStudent->gender << ',' << dob << ',' << curStudent->socialID << ',' << curStudent->specificClass << ',' << curStudent->totalCredits << endl;
		}
		fout1 << endl << string(cur->classCODE);
	}

	return true; 
}

void SchoolYear::addFirstYearClass(SpecificClass*& nowClass, SpecificClass* firstYearClass)
{	
	if(!nowClass)
	{
		nowClass = firstYearClass;
		return;
	}
	firstYearClass->nextClass = nowClass;
	nowClass = firstYearClass; 
}

void SchoolYear::outputClassedInfo() {
	cout << this->startYear << '-' << this->endYear << '\n';
	for (SpecificClass* i = this->nowClass; i != nullptr; i = i->nextClass) {
		i->outputToScreenClassInfo();
		cout << '\n';
	}
}

void SchoolYear::createNewSemester(Semester *&nowSemester , Date startDate , Date endDate )
{
	if (!nowSemester)
	{
		Semester *newSemester = new Semester(startDate , endDate);
		nowSemester = newSemester;
	}
	else
	{
		Semester *newSemester = new Semester(startDate, endDate);
		newSemester->nextSemester = nowSemester;
		nowSemester = newSemester;
	}
}

void delListSemester(Semester*& nowSemester)
{
	if (!nowSemester) return; 
	while (nowSemester->nextSemester)
	{
		Semester *delptr = nowSemester;
		nowSemester = delptr->nextSemester;
		delete delptr;
	}
	delete nowSemester; 
}

void SchoolYear::deleteSemester(Semester*& nowSemester, Semester* semester)
{
	if (!nowSemester) return; 
	if (nowSemester == semester)
	{
		Semester *delptr = nowSemester;
		nowSemester = nowSemester->nextSemester;
		delete delptr;
		return;
	}
	Semester* cur = nowSemester;
	while (cur->nextSemester)
	{
		if (cur->nextSemester == semester)
		{
			Semester* delptr = cur->nextSemester;
			cur->nextSemester = delptr->nextSemester;
			delete delptr;
			break;
		}
		cur = cur->nextSemester;
	}
}

void SchoolYear::addSpecificCLass(SpecificClass*& nowClass, char classCode[], string year) {
	SpecificClass* newClass = new SpecificClass;
	newClass->changeClassCode(classCode);
	newClass->inputFileClassInfo(year);
	if (nowClass == nullptr)
	{
		nowClass = newClass;
		return;
	}
	newClass->nextClass = nowClass;
	nowClass = newClass;
}

void SchoolYear::loadListofSpecificClasses(string year) {
	ifstream fin("SchoolYears/" + year + "/ListOfClassCode.txt");
	//cerr << year << '\n';
	char classCode[NAMELENGTH];
	while (fin.get(classCode, NAMELENGTH, '\n'))
	{
		//cerr << classCode << '\n';
		this->addSpecificCLass(this->nowClass, classCode, year);
		//cerr << this->nowClass->className << '\n';
		fin.get();
	}
	//cerr << "That's all for this year\n";
	//cerr << '\n';
}

void SchoolYear::addNewSemester(Semester*& semester) {
	if (!this->nowSemester) {
		this->nowSemester = semester;
		return;
	}
	semester->nextSemester = this->nowSemester;
	this->nowSemester = semester;
}

void SchoolYear::loadListofSemester(int amount, string year) {
	//cerr << 1 << '\n';

	int curInd = 0;
	int startYear = 0, endYear = 0;
	for (curInd; curInd < year.length() && year[curInd] != '-'; curInd++) {
		startYear *= 10;
		startYear += year[curInd] - '0';
	}
	for (++curInd; curInd < year.length(); curInd++) {
		endYear *= 10;
		endYear += year[curInd] - '0';
	}

	//cout << startYear << ' ' << endYear << '\n';

	for (int i = 1; i <= amount; i++) {

		Semester* semester = new Semester(Date(0, 0 ,startYear), Date(0 , 0 , endYear));

		string curDir = "SchoolYears/" + year + "/Semester" + (char)(i + '0') + "/Courses/";
		//cerr << curDir << '\n';

		ifstream fin;
		fin.open(curDir + "Courses.csv");

		string line, word;
		int num = 0;

		while (getline(fin, line)) {
			num++;
			if (num == 1) {
				continue;
			}
			stringstream str(line);
			int cnt = 0;
			
			int ID = 0, credit = 0, ss1 = 0, ss1Day = 0, ss2 = 0, ss2Day = 0, mStudent = 0;
			char cName[FULLNAMELENGTH];
			char tName[FULLNAMELENGTH];

			while (getline(str, word, ',')) {
				cnt++;
				stringstream stoint(word);
				switch (cnt) {
				case 1:
					stoint >> ID;
					break;
				case 2:
					for (int i = 0; i < word.length(); i++) {
						cName[i] = word[i];
					}
					cName[word.length()] = '\0';
					//cerr << strlen(cName) << '\n';
					break;
				case 3:
					for (int i = 0; i < word.length(); i++) {
						tName[i] = word[i];
					}
					tName[word.length()] = '\0';
					//cerr << strlen(tName) << '\n';
					break;
				case 4: 
					stoint >> credit;
				case 5:
					stoint >> mStudent;
					break;
				case 6:
					stoint >> ss1;
					break;
				case 7:
					stoint >> ss1Day;
					break;
				case 8:
					stoint >> ss2;
					break;
				case 9:
					stoint >> ss2Day;
					break;
				default:
					break;
				}
			}
			
			//cerr << ID << ' ' << cName << ' ' << tName << '\n';

			Course* course = new Course(ID, cName, tName, credit, ss1, ss1Day, ss2, ss2Day, mStudent);
			//cerr << 1 << '\n';
			course->addNewStudentClass(this->nowClass, curDir + course->courseName + ".csv");
			//cerr << (course->nxtStudent == nullptr);
			//cerr << 1 << '\n';

			//cerr << course->courseName << ' ' << (course->nxtStudent == nullptr) << '\n';

			/*for (Student* i = course->nxtStudent; i; i = i->nextStudent) {
				cerr << i->firstName << ' ' << i->lastName << '\n';
			}*/

			semester->addNewCourse(course);
		}

		this->addNewSemester(semester);
	}
}