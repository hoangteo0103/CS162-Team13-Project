#pragma once

#include <sstream>
#include <string.h>
#include "Constanst.h"
using namespace std;
struct DateofBirth
{
    int date, month, year;
};

class Student
{
    private:
        int No;
        bool gender;
        DateofBirth DoB;
        int socialID;
        char specificClass[NAMELENGTH];
        int totalCredits = 0;
    public:
        int studentID;
        char firstName[NAMELENGTH];
        char lastName[NAMELENGTH];
        Student* nextStudent = nullptr;
        Student();
        Student(int no, int ID, char fName[], char lName[], bool gen, DateofBirth dob,
                int sID, char sClass[], int credit);
        void addNewStudent(Student*& curStudent, Student* addStudent);  // function for staff only
        void inputFileStudentInfo(ifstream &fin);
        // void outputToScreenStudentInfo();
        void modifyStudentInfo(int no, int ID, char fName[], char lName[], bool gen, DateofBirth dob,
                            int sID, char sClass[], int credit);   // function for both student and staff
        void limitCoursesCanEnroll(); //function for staff
        void enrollCourse();    // function for student
        void getInfomation(int& no, int& ID, string& fName, string& lName, bool& gen, DateofBirth& dob,
                           int& sID, string& sClass, int& credit);
        void outputScreenInfo();
        DateofBirth getDoB(string* dob);
};

class SpecificClass
{
    private:
        char classCODE[NAMELENGTH];
        Student* classStudent = nullptr;
    public:
        char className[NAMELENGTH];
        void changeClassCode(char* classCode); 
        bool findStudent(string studentID, string& studentName);
        SpecificClass* nextClass = nullptr;
        void inputFileClassInfo(string year);
        void outputToScreenClassInfo();
};