#include "MainMenuStateTeacher.h"

void onTabSelected2(tgui::BackendGui& gui, tgui::String* curSelectedTab, tgui::Group& group_course, tgui::Group& group_student, tgui::String selectedTab)
{
    //cerr << *curSelectedTab << '\n';
    //cerr << selectedTab << '\n';
    if (selectedTab == tgui::String("Courses Information")) {
        *curSelectedTab = tgui::String("Courses Information");
        group_course.setVisible(true);
        group_student.setVisible(false);
    }
    else if (selectedTab == tgui::String("Student Information"))
    {
        *curSelectedTab = tgui::String("Student Information");
        //cerr << *curSelectedTab << '\n';
        group_course.setVisible(false);
        group_student.setVisible(true);
    }
}

void onItemSelected2(tgui::Group& group_course, SchoolYear* schoolYears, tgui::String selectedItem) {
    string sItem = selectedItem.toStdString();
    bool check = false;
    auto tArea = tgui::TextArea::create();
    tArea->setTextSize(15);
    tgui::String courseInformation = "";

    for (SchoolYear* i = schoolYears; i != nullptr && !check; i = i->nextSchoolYear) {
        for (Semester* j = i->nowSemester; j != nullptr && !check; j = j->nextSemester) {
            for (Course* k = j->nowCourse; k != nullptr && !check; k = k->nextCourse) {
                if (!sItem.compare(k->courseName)) {
                    check = true;
                    courseInformation += tgui::String(k->courseID) + '\n';
                    //cerr << courseInformation << '\n';
                    courseInformation += tgui::String(k->courseName) + '\n';
                    //cerr << k->courseName << '\n';
                    courseInformation += tgui::String(k->teacherName) + '\n';
                    //cerr << k->teacherName << '\n';
                    courseInformation += tgui::String(k->getFirstSessionDate()) + '\n';
                    courseInformation += tgui::String(k->getSecondSessionDate()) + '\n';
                }
            }
        }
    }

    if (check) {
        tArea->setText(courseInformation);
        group_course.get<tgui::ScrollablePanel>("ScrollablePanel1")->add(tArea, "TArea");
    }
    else {
        group_course.get<tgui::ScrollablePanel>("ScrollablePanel1")->removeAllWidgets();
    }
}


bool addComponents2(tgui::BackendGui& gui, SchoolYear*& schoolYears,  tgui::Group& group_course, tgui::Group& group_student)
{
    /*tgui::Theme theme{ "themes/Black.txt" };

    auto label = tgui::Label::create();
    label->setRenderer(theme.getRenderer("Label"));
    tgui::String className;

    SchoolYear* curSchoolYear = nullptr;

    for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        string studentName;

        tgui::String years = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);
        group_course.get<tgui::TreeView>("TreeView1")->addItem({ years });

        if (i->nowClass->findStudent(studentID.toStdString(), studentName)) {
            curSchoolYear = i;
            tgui::String t = studentName;
            label->setText(t);
        }
    }

    label->setPosition(10, 10);
    label->setTextSize(20);
    group_course.add(label);

    if (!curSchoolYear) return false;

    tgui::String curYears = tgui::String(curSchoolYear->startYear) + '-' + tgui::String(curSchoolYear->endYear);

    int curSemester = 4;

    tgui::String curDirectory = "SchoolYears/" + tgui::String(curSchoolYear->startYear) + "-" + tgui::String(curSchoolYear->endYear);

    for (Semester* i = curSchoolYear->nowSemester; i; i = i->nextSemester) {
        curSemester--;
        tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
        string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
        group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr });
        for (Course* j = i->nowCourse; j; j = j->nextCourse) {
            if (j->findStudent(curDir, studentID.toStdString())) {
                tgui::String item = j->courseName;
                group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr, item });
            }
        }

    }

    gui.get<Tabs>("Tabs1")->select("Courses Information");
    tgui::String* curSelectedTab = new tgui::String;
    *curSelectedTab = "Courses Information";
    group_course.get<tgui::TreeView>("TreeView1")->onItemSelect(&onItemSelected2, ref(group_course), schoolYears);
    gui.get<Tabs>("Tabs1")->onTabSelect(&onTabSelected2, ref(gui), curSelectedTab, ref(group_course), ref(group_student));
    */

    return true;
}

void updateTextSizeMainMenuTeacher(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of 
}

void loadWidgetsMainMenuTeacher(tgui::BackendGui& gui)
{
    gui.loadWidgetsFromFile("MainMenuForm2.txt");

    // Specify an initial text size instead of using the default value
    updateTextSizeMainMenuTeacher(gui);

    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui] { updateTextSizeMainMenuTeacher(gui); });
    //gui.get<tgui::Button>("Button1")->onPress(&login, gui, gui.get<tgui::EditBox>("EditBox1"), gui.get<tgui::EditBox>("EditBox2"), std::ref(accounts));
}

void run_mainmenu_teacher(BackendGui& gui, tgui::String teacher_name)
{
    loadWidgetsMainMenuTeacher(gui);
    auto group_course = tgui::Group::create();
    auto group_student = tgui::Group::create();
    group_student->loadWidgetsFromFile("StudentInformationForm.txt");
    group_course->loadWidgetsFromFile("CourseInformationForm.txt");
    SchoolYear* schoolYears = nullptr;
    loadListofSchoolYears(schoolYears);
    //addComponents(gui, schoolYears, , *group_course, *group_student);
    gui.add(group_course);
    gui.add(group_student);
    group_course->setVisible(true);
    group_student->setVisible(false);
}