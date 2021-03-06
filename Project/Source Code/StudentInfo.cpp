#include "StudentInfo.h"
#include <string>
#include <fstream>
using namespace tgui;

void onStudentInfoSelected(tgui::Group& group_studentInfo, tgui::Group& group_student)
{
    group_studentInfo.setVisible(true);
    group_student.setVisible(false);
}

void init_group_student(tgui::Group& group_studentInfo)
{
    group_studentInfo.loadWidgetsFromFile("StudentInfoForm.txt");
}
void onUpdateSelected(tgui::Group& group_studentInfo, Student& student)
{
    int id = atoi(group_studentInfo.get<EditBox>("StudentIDBox")->getText().toStdString().c_str());
    char firstNAME[NAMELENGTH] , lastNAME[NAMELENGTH] ;
    strcpy_s(firstNAME, group_studentInfo.get<EditBox>("FirstNameBox")->getText().toStdString().c_str());
    strcpy_s(lastNAME, group_studentInfo.get<EditBox>("LastNameBox")->getText().toStdString().c_str());
    bool gender = group_studentInfo.get<tgui::EditBox>("GenderBox")->getText() == tgui::String("Male");
    int sId = atoi(group_studentInfo.get<EditBox>("StudentIDBox")->getText().toStdString().c_str());
    DateofBirth dob = student.getDoB(&group_studentInfo.get<EditBox>("DoBBox")->getText().toStdString()); 
    int credit = atoi(group_studentInfo.get<EditBox>("CreditBox")->getText().toStdString().c_str());
    student.modifyStudentInfo(student.No, id, firstNAME, lastNAME, gender, dob, sId, student.specificClass, credit);
    group_studentInfo.get<Label>("InfoUpdate")->setVisible(true); 
    group_studentInfo.get<Label>("InfoUpdate")->setText("Change Info Successfully");
}

void onChangePasswordSelected(Group& group_studentInfo, Student& student)
{
    char curPass[30];
    strcpy_s(curPass ,   group_studentInfo.get<EditBox>("GetCur")->getText().toStdString().c_str());
    char newPass[30];
    strcpy_s(newPass, group_studentInfo.get<EditBox>("GetNew")->getText().toStdString().c_str());
    char confirmPass[30];
    strcpy_s(confirmPass, group_studentInfo.get<EditBox>("GetConfirm")->getText().toStdString().c_str());
    int id; 
    char pass[30];
    ifstream fin_acc("StudentAccount.txt" );
    fstream fin_pass("StudentPassword.txt");
    int stId = atoi(group_studentInfo.get<EditBox>("StudentIDBox")->getText().toStdString().c_str());
    while (fin_acc >> id)
    {
        string s;
        fin_pass >> s;
        strcpy_s(pass, s.c_str());
        cout << curPass << ' ' << stId << ' ' <<  id << ' ' << pass << endl;
        if (id == stId)
        {
            if (strcmp(pass , curPass) == 0)
            {
                cout << "DM" << endl;
                if (strcmp(newPass, confirmPass) != 0 )
                {
                    
                    cout << newPass << ' ' << confirmPass << endl;
                    group_studentInfo.get<Label>("InfoUpdate")->setText("Wrong Confirm Password");
                    group_studentInfo.get<Label>("InfoUpdate")->setVisible(true);
                    return;
                }
                if (group_studentInfo.get<EditBox>("GetNew")->getText() == "")
                {
                    return;
                }
                strcpy_s(pass, newPass);

                ifstream fin_change("StudentPassword.txt");
                string ss;
                vector<string> vc;
                while (fin_change >> ss)
                {
                    vc.push_back(ss);
                }
                ofstream fout_change("StudentPassword.txt");
                for (string i : vc)
                {
                    if (i == s)
                    {
                        fout_change << group_studentInfo.get<EditBox>("GetNew")->getText().toStdString() << endl;
                    }
                    else fout_change << i << endl;
                }

                group_studentInfo.get<Label>("InfoUpdate")->setText("Change Password Succesfully");
                group_studentInfo.get<Label>("InfoUpdate")->setVisible(true);
                group_studentInfo.get<EditBox>("GetNew")->setText("");
                group_studentInfo.get<EditBox>("GetCur")->setText("");
                group_studentInfo.get<EditBox>("GetConfirm")->setText("");
                

            }
            else {
                group_studentInfo.get<Label>("InfoUpdate")->setText("Wrong Password");
                group_studentInfo.get<Label>("InfoUpdate")->setVisible(true);
                return;
            }
            break;
        }
    }


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
    group_studentInfo.get<Button>("UpdateInformation")->onClick(&onUpdateSelected, ref(group_studentInfo) , ref(student));
    group_studentInfo.get<Button>("ChangePassword")->onClick(&onChangePasswordSelected, ref(group_studentInfo) , ref(student));
}