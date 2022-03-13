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