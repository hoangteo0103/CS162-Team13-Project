#pragma once

#include "Courses.h"

#define NAMELENGTH 20
#define FULLNAMELENGTH 50
#define MAXSTUDENTNUM 50
#define S1 7.30
#define S2 9.30
#define S3 13.30
#define S4 15.30

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


class Semester
{
    private:
        int No;
        int startDate, endDate;
        int startSchoolYear, endSchoolYear;
        Course* newCourse = nullptr;
        Semester* nextSemester = nullptr;
    public:
        void viewCourseList();
        void deleteCourse();
};

class SchoolYear
{
    private:
        int startYear, endYear;
        Semester* Smt = nullptr;
        SchoolYear* nextSchoolYear;
    public:
        void createSchoolYear();
};