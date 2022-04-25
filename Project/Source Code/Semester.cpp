#include <fstream>
#include <iostream>
using namespace std;

#include "Semester.h"

Date::Date()
{
	this->day = 1;
	this->month = 1;
	this->year = 1;
}
void ScoreBoard::editScoreBoard()
{

}
void Semester::viewCourseList()
{

}

Semester::Semester(Date startDate , Date endDate)
{
	this->startDate = startDate;
	this->endDate = endDate; 
	nowCourse = nullptr;
}

void Semester::deleteCourse(Course *&nowCourse ,Course* course)
{
	if (!nowCourse) return; 
	numCourse--;
	if (nowCourse == course)
	{
		Course* delptr = nowCourse;
		nowCourse = nowCourse->nextCourse;
		delete delptr;
		return;
	}
	Course* cur = nowCourse; 
	while (cur->nextCourse)
	{
		if (cur->nextCourse == course)
		{
			Course* delptr = cur->nextCourse;
			cur->nextCourse = delptr->nextCourse;
			delete delptr; 
			break;
		}
		cur = cur->nextCourse; 
	}
}

void Semester::delListCourse(Course*& nowCourse)
{
	if (!nowCourse) return; 
	while (nowCourse->nextCourse)
	{
		Course* delptr = nowCourse->nextCourse;
		nowCourse->nextCourse = delptr->nextCourse;
		delete delptr;
	}
	delete nowCourse;
}

void Semester::addNewCourse(Course* course)
{
	this->numCourse++;
	//cerr << 1 << '\n';
	if (!this->nowCourse)
	{
		nowCourse = course;
		return; 
	}
	course->nextCourse = this->nowCourse;
	this->nowCourse = course; 
}


