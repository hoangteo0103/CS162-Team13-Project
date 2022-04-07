#include "StudentInfo.h"

void onStudentInfoSelected(tgui::Group& group_studentInfo, tgui::Group& group_student)
{
    group_studentInfo.setVisible(true);
    group_student.setVisible(false);
}

void init_group_student(tgui::Group& group_studentInfo)
{
    group_studentInfo.loadWidgetsFromFile("StudentInfoForm.txt");
}

void loadInfoWidget(tgui::Group& group_studentInfo, Student& student) {
    init_group_student(group_studentInfo);
    group_studentInfo.get<tgui::EditBox>("StudentIDBox")->setText(tgui::String(student.studentID));
    group_studentInfo.get<tgui::EditBox>("FirstNameBox")->setText(tgui::String(student.firstName));
    group_studentInfo.get<tgui::EditBox>("LastNameBox")->setText(tgui::String(student.lastName));
    if (student.gender) {
        group_studentInfo.get<tgui::EditBox>("GenderBox")->setText(tgui::String("Male"));
    }
    else {
        group_studentInfo.get<tgui::EditBox>("GenderBox")->setText(tgui::String("Female"));
    }
    group_studentInfo.get<tgui::EditBox>("SocialIDBox")->setText(tgui::String(student.socialID));
    tgui::String dob = tgui::String(student.DoB.date) + '/' + tgui::String(student.DoB.month) + '/' + tgui::String(student.DoB.year);
    group_studentInfo.get<tgui::EditBox>("DoBBox")->setText(dob);
    group_studentInfo.get<tgui::EditBox>("CreditBox")->setText(tgui::String(student.totalCredits));
}