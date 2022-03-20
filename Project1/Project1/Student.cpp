#include <fstream>
#include <iostream>

using namespace std;

#include "Student.h"

void Student::addNewStudent(Student* pHeadStudent)
{
    Student* curStudent = pHeadStudent;
    while (curStudent != nullptr)
        curStudent = curStudent->nextStudent;
    curStudent = new Student;
    cin >> curStudent->No;
    cin >> curStudent->studentID;
    cin.get(firstName, NAMELENGTH);
    cin.get(lastName, NAMELENGTH);
    cin >> gender;
    cin >> DoB.date;
    cin >> DoB.month;
    cin >> DoB.year;
    cin >> socialID;
}

void Student::modifyStudentInfo()
{
    int action;
    do
    {
        cout << "Student infomation:\n";
        cout << "   1. No: " << No << endl;
        cout << "   2. StudentID: " << studentID << endl;
        cout << "   3. Student name: " << firstName << " " << lastName << endl;
        cout << "   4. Student gender: " << gender << endl;
        cout << "   5. Student DoB: " << DoB.date << "/" << DoB.month << "/" << DoB.year << endl;
        cout << "   6. Student Social ID: " << socialID << endl;
        cout << "   7. Total credits (only staff can modify): " << totalCredits << endl;
        cout << "which student's infomation that you want to modify (use number 1 -> 7 respectively, 7 to exit): ";
        cin >> action;
        switch (action)
        {
            case 1:
                cout << "Please input again the student No: ";
                cin >> No;
                break;
            case 2:
                cout << "Please input again the student ID: ";
                cin >> studentID;
                break;
            case 3:
                cout << "Please input again the student first name: ";
                cin.get(firstName,NAMELENGTH);
                cout << "Please input again the student last name: ";
                cin.get(lastName,NAMELENGTH);
                break;
            case 4:
                cout << "Please input again the student gender (0 for male and 1 for female): ";
                cin >> gender;
                break;
            case 5:
                cout << "Please input again the student Date of birth: ";
                cin >> No;
                break;
            case 6:
                cout << "Please input again the student No: ";
                cin >> No;
                break;
        }
    } while (action >= 1 && action <=6);
    
    
}

void Student::inputFileStudentInfo(ifstream &fin)
{
    char tmp[NAMELENGTH];
    fin.get(tmp,',');
    No = (int)tmp;
    fin.get(tmp,',');
    studentID = (int)tmp;
    fin.get(firstName, ',');
    fin.get(lastName, ',');
    fin.get(tmp, ',');
    if (tmp == "1")
        gender = true;
    else
        gender = false;
    fin.get(tmp, '/');
    DoB.date = (int)tmp;
    fin.get(tmp, '/');
    DoB.month = (int)tmp;
    fin.get(tmp, ',');
    DoB.year = (int)tmp;
    fin.get(tmp, ',');
    socialID = (int)tmp;
    fin.get(specificClass, '\n');
}

void limitCoursesCanEnroll()
{

}

void enrollCourse()
{

}

void SpecificClass::inputFileClassInfo()
{
    ifstream fin (classCODE[NAMELENGTH] + ".txt");
    fin.ignore(999,'\n');
    Student* curStudent = classStudent;
    while (!fin.eof())
    {
        curStudent->inputFileStudentInfo(fin);
        curStudent->nextStudent = new Student;
        curStudent = curStudent->nextStudent;
    }
    fin.close();
}

void outputToScreenClassInfo()
{

}