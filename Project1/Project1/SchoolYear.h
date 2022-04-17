#pragma once
#include <iostream>
#include <fstream>
#include "Semester.h"
#include "Student.h"
class SchoolYear
{
private:
    
public:
    int startYear, endYear;
    SchoolYear* nextSchoolYear;
    Semester* nowSemester = nullptr;
    SpecificClass* nowClass = nullptr;
    SchoolYear(int startYear, int endYear);
    bool createNewSchoolYear();
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
