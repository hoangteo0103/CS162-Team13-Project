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