#pragma once

#include "Courses.h"

class ScoreBoard
{
    private:
        int No, studentID;
        char studentFullName[FULLNAMELENGTH];
        float totalMark;
        float finalMark;
        float midtermMark;
        float otherMark;
        ScoreBoard* nextScoreBoard = nullptr;
    public:
        void editScoreBoard();
};


struct Date {
    int day, month, year;
    Date();
    Date(int day_z, int month_z, int year_z)
    {
        this->day = day_z;
        this->month = month_z;
        this->year = year_z;
    };

};

class Semester
{
    private:
 
    public:
        int No;
        Date startDate, endDate;
        int startSchoolYear, endSchoolYear;
        int numCourse = 0;
        Semester(Date startDate , Date endDate);
        Semester* nextSemester = nullptr;
        Course* nowCourse = nullptr;
        void viewCourseList();
        void deleteCourse(Course*& nowCourse, Course* course);
        void delListCourse(Course*& nowCourse);
        void addNewCourse(Course* course);
};

