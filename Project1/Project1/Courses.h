#pragma once

#include <vector>
#include <sstream>
#include "Student.h"
#include <string>
using namespace std; 

class Course
{
    private:
        int courseID;
        char courseName[NAMELENGTH];
        char teacherName[NAMELENGTH];
        int credits;
        int maximumStudentNum = MAXSTUDENTNUM;
        int session1, session2;
        Student* classStudents;
    public:
        Course();
        Course(int ID, char cName[], char tName[], int credit, int ss1, int ss2, int mStudent = 0);
        Course* nextCourse = nullptr; 
        void addNewStudent(Student* student);
        int strToNum(string* num);
        void delListStudent();
        void inputFileClassInfo();
        void updateCourseInfo(int ID, char cName[], char tName[], int credit, int ss1, int ss2, int mStudent);
        void outputToScreenClassInfo();
        void exportStudentList(fstream& fout);
        void importScoreBoard();
        void viewScourBoard();
        void updateResult();

        DateofBirth getDoB(string* dob);
};