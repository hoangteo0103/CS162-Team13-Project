#pragma once

#define NAMELENGTH 20
#define FULLNAMELENGTH 50
#define MAXSTUDENTNUM 50
#define S1 7.30
#define S2 9.30
#define S3 13.30
#define S4 15.30

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
        void addNewStudent();
        // void inputFileStudentInfo();
        // void outputToScreenStudentInfo();
        void modifyStudentInfo();
        void enrollCourse();
};

class SpecificClass
{
    private:
        char className[NAMELENGTH];
        char classCODE[NAMELENGTH];
        Student* classStudent;
        SpecificClass* nextClass;
    public:
        Student* createNewStudent();
        void inputFileClassInfo();
        void outputToScreenClassInfo();
};