#pragma once
#include <iostream>
#include <fstream>
#include "Semester.h"
#include "Student.h"
class SchoolYear
{
private:
    int startYear, endYear;
    Semester* nowSemester = nullptr;
    SpecificClass *nowClass = nullptr;
public:
    SchoolYear* nextSchoolYear;
    SchoolYear(int startYear, int endYear);
    void addNewSemester(Semester*& semester);
    void addFirstYearClass(SpecificClass*& nowClass, SpecificClass* firstYearclass);
    void createNewSemester(Semester *&nowSemester, int startDate, int endDate);
    void delListSemester(Semester*& nowSemester);
    void deleteSemester(Semester*& nowSemester, Semester* semester);
    void addSpecificCLass(SpecificClass*& nowClass, char classCode[], string year);
    void loadListofSpecificClasses(string year);
    void loadListofSemester(int amount, string year);
    void outputClassedInfo();
};
