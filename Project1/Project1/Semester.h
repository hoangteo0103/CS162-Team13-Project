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
 
    public:
        Semester(int startDate , int endDate);
        Semester* nextSemester = nullptr;
        Course* nowCourse = nullptr;
        void viewCourseList();
        void deleteCourse(Course*& nowCourse, Course* course);
        void delListCourse(Course*& nowCourse);
        void addNewCourse(Course* course);
};

