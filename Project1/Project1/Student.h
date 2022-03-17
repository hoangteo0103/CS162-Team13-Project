#pragma once

#include "Constanst.h"

struct DateofBirth
{
    int date, month, year;
};

class Student
{
    private:
        int No;
        int studentID;
        char firstName[NAMELENGTH];
        char lastName[NAMELENGTH];
        bool gender;
        DateofBirth DoB;
        int socialID;
        char specificClass[NAMELENGTH];
        int totalCredits = 0;
        Student* nextStudent = nullptr;
    public:
        void addNewStudent(Student* pHeadStudent);  // function for staff only
        void inputFileStudentInfo(ifstream fin);
        // void outputToScreenStudentInfo();
        void modifyStudentInfo();   // function for both student and staff
        void limitCoursesCanEnroll(); //function for staff
        void enrollCourse();    // function for student
};

class SpecificClass
{
    private:
        char className[NAMELENGTH];
        char classCODE[NAMELENGTH];
        Student* classStudent;
        SpecificClass* nextClass;
    public:
        void inputFileClassInfo();
        void outputToScreenClassInfo();
};