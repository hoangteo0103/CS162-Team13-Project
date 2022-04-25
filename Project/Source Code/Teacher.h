#pragma once
#ifndef TEACHER_H
#define TEACHER_H
#include "Constanst.h"
#include "Courses.h"
struct DateofBirth
{
    int date, month, year;
}; 
class Teacher
{
private :
    int No;
    char firstName[NAMELENGTH];
    char lastName[NAMELENGTH];
    bool gender;
    DateofBirth DoB;
    int socialID;
};
#endif
