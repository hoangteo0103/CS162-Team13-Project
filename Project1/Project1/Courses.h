#pragma once

#include "Student.h"

class Course
{
    private:
        int courseID;
        char courseName[NAMELENGTH];
        char teacherName[NAMELENGTH];
        int credits;
        int maximumStudentNum = MAXSTUDENTNUM;
        int session1, session2;
        Student* classStudent;
    public:
        Student* createNewStudent();
        void inputFileClassInfo();
        void updateCourseInfo();
        void outputToScreenClassInfo();
        void exportStudentList();
        void importScoreBoard();
        void viewScourBoard();
        void updateResult();
};