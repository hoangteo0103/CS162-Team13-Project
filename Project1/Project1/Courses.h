#pragma once

#include "Student.h"

#define NAMELENGTH 20
#define FULLNAMELENGTH 50
#define MAXSTUDENTNUM 50
#define S1 7.30
#define S2 9.30
#define S3 13.30
#define S4 15.30

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