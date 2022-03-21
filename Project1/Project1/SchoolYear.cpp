#include "SchoolYear.h"

SchoolYear::SchoolYear(int startYear , int endYear)
{
	this->startYear = startYear;
	this->endYear = endYear;
	this->nowSemester = nullptr; 
}

void addFirstYearClass(SpecificClass*& nowClass, SpecificClass* firstYearClass)
{
	if(!nowClass)
	{
		nowClass = firstYearClass;
		return;
	}
	firstYearClass->nextClass = nowClass;
	nowClass = firstYearClass; 
}

void createNewSemester(Semester *&nowSemester , int startDate , int endDate )
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

void deleteSemester(Semester*& nowSemester, Semester* semester)
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