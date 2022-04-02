#pragma once

#include <vector>
#include <sstream>
#include "Student.h"
#include <string>
using namespace std; 

struct IDNode {
    int sID;
    IDNode* nextNode = nullptr;
};

class Course
{
    private:
        int courseID;
        int credits;
        int currentStudentNum = 0;
        int maximumStudentNum = MAXSTUDENTNUM;
        int session1, session1Day, session2, session2Day;
        IDNode* nextID = nullptr;

    public:
        char courseName[FULLNAMELENGTH];
        char teacherName[FULLNAMELENGTH];
        Course();
        Course(int ID, char cName[], char tName[], int credit, int ss1, int ss1Day, int ss2, int ss2Day, int mStudent = 0);
        Course* nextCourse = nullptr; 
        void addNewStudent(IDNode* student);
        int strToNum(string* num);
        void delListStudent();
        void inputFileClassInfo(string curDir);
        void updateCourseInfo(int ID, char cName[], char tName[], int credit, int ss1, int ss1Day, int ss2, int ss2Day, int mStudent);
        void outputToScreenClassInfo();
        void exportStudentList(fstream& fout);
        void importScoreBoard();
        void viewScourBoard();
        void updateResult();

        DateofBirth getDoB(string* dob);
};