#pragma once
#include <iostream>
#include <fstream>
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
    IDNode* nextID = nullptr;

public:
    Student* nxtStudent = nullptr;
    char courseName[FULLNAMELENGTH];
    int courseID;
    char teacherName[FULLNAMELENGTH];
    int credits;
    int score = 0 ; 
    int currentStudentNum = 0;
    int maximumStudentNum = MAXSTUDENTNUM;
    int session1, session1Day, session2, session2Day;
    Course();
    Course(int ID, char cName[], char tName[], int credit, int ss1, int ss1Day, int ss2, int ss2Day, int mStudent = 0);
    Course* nextCourse = nullptr;
    void addNewStudent(IDNode* student);
    void addNewStudentClass(SpecificClass* nowClass, string curDir);
    int strToNum(string* num);
    void delListStudent();
    void inputFileClassInfo(string curDir);
    void updateCourseInfo(int ID, char cName[], char tName[], int credit, int ss1, int ss1Day, int ss2, int ss2Day, int mStudent);
    void outputToScreenClassInfo();
    void exportStudentList(fstream& fout);
    bool findStudent(string curDir, string studentID);
    void importScoreBoard();
    void viewScourBoard();
    void updateResult();
    string convertoABC(int score); 
    string getFirstSessionDate();
    string getSecondSessionDate();
    DateofBirth getDoB(string* dob);
};