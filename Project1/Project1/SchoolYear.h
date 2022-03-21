#pragma once
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
    void addFirstYearClass(SpecificClass*& nowClass, SpecificClass* firstYearclass);
    void createNewSemester(Semester *&nowSemester, int startDate, int endDate);
    void delListSemester(Semester*& nowSemester);
    void deleteSemester(Semester*& nowSemester, Semester* semester);
};
