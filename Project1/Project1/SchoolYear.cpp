#include "SchoolYear.h"

SchoolYear::SchoolYear(int startYear, int endYear)
{
	this->startYear = startYear;
	this->endYear = endYear;
	this->nowSemester = nullptr; 
	this->nowClass = nullptr;
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

void SchoolYear::createNewSemester(Semester *&nowSemester , int startDate , int endDate )
{
	if (!nowSemester)
	{
		Semester *newSemester = new Semester(startDate , endDate);
		nowSemester = newSemester;
	}
	Semester *newSemester = new Semester(startDate, endDate);
	newSemester->nextSemester = nowSemester;
	nowSemester = newSemester;
}

void delListSemester(Semester*& nowSemester)
{
	if (!nowSemester) return; 
	while (nowSemester->nextSemester)
	{
		Semester *delptr = nowSemester;
		nowSemester->nextSemester = delptr->nextSemester;
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
		fin.get();
	}
	//cerr << "That's all for this year\n";
	//cerr << '\n';
}