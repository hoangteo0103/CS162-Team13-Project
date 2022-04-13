#include "Action.h"
void onClickedLogout(BackendGui& gui)
{
    run_login(gui);
}

void onParticipants(Group& group_course, Course* curCourse)
{
    group_course.get<ListView>("PaList")->setVisible(true);
    group_course.get<ListView>("PaList")->removeAllColumns();
    group_course.get<ListView>("PaList")->addColumn("Name", 100, ListView::ColumnAlignment::Center);
    group_course.get<ListView>("PaList")->addColumn("Roles", 100, ListView::ColumnAlignment::Center);
    group_course.get<ListView>("PaList")->addColumn("Group", 100, ListView::ColumnAlignment::Center);
    //for(IDNode* )
}

void onTabSelected(tgui::BackendGui& gui, tgui::String* curSelectedTab, vector<tgui::Group*>* vc, tgui::String selectedTab)
{
    //cerr << *curSelectedTab << '\n';
    //cerr << selectedTab << '\n';

    //cerr << vc->size() << '\n';

    int selectedIndex = 0;
    if (selectedTab == tgui::String("Courses Information")) {
        *curSelectedTab = tgui::String("Courses Information");
        selectedIndex = 0;
    }
    else if (selectedTab == tgui::String("Student Information"))
    {
        *curSelectedTab = tgui::String("Student Information");
        selectedIndex = 1;
    }

    //cerr << selectedIndex << '\n';

    for (int i = 0; i < (*vc).size(); i++)
    {
        (*vc)[i]->setVisible(false);
    }

    //(*vc)[1] = 5;
    (*vc)[selectedIndex]->setVisible(true);
}

void showGroupCourse(Group& group_course, bool check)
{

    group_course.get<ListView>("PaList")->setVisible(false);
    group_course.get<Label>("Teacher Name")->setVisible(check);
    group_course.get<Label>("Course Name")->setVisible(check);
    group_course.get<Label>("People")->setVisible(check);
    group_course.get<Label>("Date")->setVisible(check);
    group_course.get<Picture>("Picture1")->setVisible(check);
    group_course.get<Picture>("Picture2")->setVisible(check);
    group_course.get<Picture>("Picture3")->setVisible(check);
    group_course.get<TextArea>("TextArea1")->setVisible(check);
    group_course.get<TextArea>("TextArea2")->setVisible(check);
    group_course.get<Button>("Participants")->setVisible(check);
}

void onItemSelected(tgui::Group& group_course, SchoolYear* schoolYears, Course* curCourse, Student student, tgui::String selectedItem) {
    string sItem = selectedItem.toStdString();
    bool check = false;
    tgui::String courseInformation = "";

    for (SchoolYear* i = schoolYears; i != nullptr && !check; i = i->nextSchoolYear) {
        for (Semester* j = i->nowSemester; j != nullptr && !check; j = j->nextSemester) {
            for (Course* k = j->nowCourse; k != nullptr && !check; k = k->nextCourse) {
                if (!sItem.compare(k->courseName)) {
                    check = true;
                    curCourse = k;
                    group_course.get<Label>("Course Name")->setTextSize(30);
                    group_course.get<Label>("Course Name")->setText(k->courseName + tgui::String("  -  ") + student.specificClass);
                    group_course.get<Label>("Teacher Name")->setTextSize(13);
                    group_course.get<Label>("Teacher Name")->setText(k->teacherName);
                    courseInformation += '\n' + tgui::String(k->getFirstSessionDate()) + '\n' + '\n' + '\n';
                    courseInformation += tgui::String(k->getSecondSessionDate()) + '\n';
                    group_course.get<TextArea>("TextArea2")->setText(courseInformation);
                    group_course.get<TextArea>("TextArea2")->setTextSize(30);
                    continue;
                    //cerr << k->teacherName << '\n';
                }
            }
        }
    }
    showGroupCourse(group_course, check);
}