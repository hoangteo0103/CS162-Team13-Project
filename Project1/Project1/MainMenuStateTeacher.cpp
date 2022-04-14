#include "MainMenuState.h"      

void onTabSelected2(tgui::BackendGui& gui, tgui::String* curSelectedTab, vector<tgui::Group*>* vc, tgui::String selectedTab)
{
    //cerr << *curSelectedTab << '\n';
    //cerr << selectedTab << '\n';

    //cerr << vc->size() << '\n';

    int selectedIndex = 0;
    if (selectedTab == tgui::String("Courses Information")) {
        *curSelectedTab = tgui::String("Courses Information");
        selectedIndex = 0;
    }
    else if (selectedTab == tgui::String("Teacher Information"))
    {
        *curSelectedTab = tgui::String("Teacher Information");
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

void onItemSelected2(tgui::Group& group_course, SchoolYear* schoolYears, Course* curCourse, tgui::String selectedItem) {
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
                    group_course.get<Label>("Course Name")->setText(k->courseName);
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

bool addComponents2(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String teacherName, tgui::Group& group_course,
    tgui::Group& group_student, tgui::Group& group_scoreboard, tgui::Group& group_studentInfo)
{
    tgui::Theme theme{ "themes/Black.txt" };

    auto label = tgui::Label::create();
    label->setRenderer(theme.getRenderer("Label"));
    label->setText(teacherName);
    label->setPosition(10, 10);
    label->setTextSize(20);
    group_course.add(label);
    if (!schoolYears) return false;

    for (SchoolYear* curSchoolYear = schoolYears; curSchoolYear; curSchoolYear = curSchoolYear->nextSchoolYear)
    {
        tgui::String curYears = tgui::String(curSchoolYear->startYear) + '-' + tgui::String(curSchoolYear->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(curSchoolYear->startYear) + "-" + tgui::String(curSchoolYear->endYear);

        for (Semester* i = curSchoolYear->nowSemester; i; i = i->nextSemester) {
            curSemester--;
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
            group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr });
            for (Course* j = i->nowCourse; j; j = j->nextCourse) {
                {
                    tgui::String item = j->courseName;
                    group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr, item });
                }
            }

        }
    }
    
    gui.get<Tabs>("Tabs1")->select("Courses Information");
    tgui::String* curSelectedTab = new tgui::String;
    *curSelectedTab = "Courses Information";
    //cerr << vc.size() << '\n';
    vector<tgui::Group*>* vc = new vector<tgui::Group*>;
    vc->push_back(&group_course);
    vc->push_back(&group_student);
    vc->push_back(&group_scoreboard);
    vc->push_back(&group_studentInfo);
    Course* curCourse = new Course;
    group_course.get<Button>("Participants")->onClick(&onParticipants, ref(group_course), curCourse);
    group_course.get<tgui::TreeView>("TreeView1")->onItemSelect(&onItemSelected2, ref(group_course), schoolYears, curCourse);
    //group_student.get<tgui::Button>("ScoreBoard")->onClick(&onScoreboardSelected, ref(group_scoreboard), ref(group_student));
    //group_student.get<tgui::Button>("Student Info")->onClick(&onStudentInfoSelected, ref(group_studentInfo), ref(group_student));
    gui.get<Tabs>("Tabs1")->onTabSelect(&onTabSelected2, ref(gui), curSelectedTab, vc);
    gui.get<Button>("Logout")->onClick(&onClickedLogout, ref(gui));
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

void hideGroupCourseTeacher(Group& group_course)
{
    group_course.get<Label>("Course Name")->setVisible(false);
    group_course.get<Label>("Teacher Name")->setVisible(false);
    group_course.get<Label>("People")->setVisible(false);
    group_course.get<Label>("Date")->setVisible(false);
    group_course.get<TextArea>("TextArea2")->setVisible(false);
    group_course.get<Picture>("Picture1")->setVisible(false);
    group_course.get<Picture>("Picture2")->setVisible(false);
    group_course.get<Picture>("Picture3")->setVisible(false);
    group_course.get<TextArea>("TextArea1")->setVisible(false);
    group_course.get<Button>("Participants")->setVisible(false);
    group_course.get<ListView>("PaList")->setVisible(false);
}

void run_mainmenu_teacher(BackendGui& gui, tgui::String teacherName)
{
    loadWidgetsMainMenuTeacher(gui);
    auto group_course = tgui::Group::create();
    auto group_student = tgui::Group::create();
    auto group_scoreboard = tgui::Group::create();
    auto group_studentInfo = tgui::Group::create();
    group_student->loadWidgetsFromFile("TeacherInformationForm.txt");
    group_course->loadWidgetsFromFile("CourseInformationForm.txt");
    SchoolYear* schoolYears = nullptr;
    loadListofSchoolYears(schoolYears);
    addComponents2(gui, schoolYears, teacherName, *group_course, *group_student, *group_scoreboard, *group_studentInfo);
    gui.add(group_course);
    gui.add(group_student);
    gui.add(group_scoreboard);
    gui.add(group_studentInfo);
    group_course->setVisible(true);
    group_student->setVisible(false);
    group_scoreboard->setVisible(false);
    group_studentInfo->setVisible(false);
    hideGroupCourseTeacher(*group_course);
}
