#include "MainMenuStateTeacher.h"      

Course* curCourse2;

bool addComponents2(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String teacherName, tgui::Group& group_course,
    tgui::Group& group_student, tgui::Group& group_scoreboard, tgui::Group& group_studentSB, tgui::Group& group_studentInfo, tgui::Group& group_small_studentInfo, tgui::Group& group_create)
{
    tgui::Theme theme{ "themes/Black.txt" };

    auto label = tgui::Label::create();
    label->setRenderer(theme.getRenderer("Label"));
    label->setText(teacherName);
    label->setPosition(60, 15);
    label->setTextSize(20);
    group_course.add(label);
    if (!schoolYears) return false;

    for (SchoolYear* curSchoolYear = schoolYears; curSchoolYear; curSchoolYear = curSchoolYear->nextSchoolYear)
    {
        tgui::String curYears = tgui::String(curSchoolYear->startYear) + '-' + tgui::String(curSchoolYear->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(curSchoolYear->startYear) + "-" + tgui::String(curSchoolYear->endYear);

        ifstream finTmp;
        finTmp.open(curDirectory.toStdString() + "/ListofSemester.txt");
        finTmp >> curSemester; curSemester++;
        finTmp.close();

        if (curSchoolYear->nowSemester == NULL)
        {
            group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears });
        }

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

    loadcreatewidget(group_create);
    loadScoreBoardWidget(group_scoreboard, schoolYears);
    loadStudentWidget(group_studentInfo, schoolYears);
    loadSBWidgets(group_studentSB, schoolYears);

    gui.get<Tabs>("Tabs1")->select("Courses Information");
    tgui::String* curSelectedTab = new tgui::String;
    *curSelectedTab = "Courses Information";
    //cerr << vc.size() << '\n';
    vector<tgui::Group*>* vc = new vector<tgui::Group*>;
    vc->push_back(&group_course);
    vc->push_back(&group_student);
    vc->push_back(&group_scoreboard);
    vc->push_back(&group_studentSB);
    vc->push_back(&group_studentInfo);
    vc->push_back(&group_small_studentInfo);
    vc->push_back(&group_create);
    curCourse2 = new Course;
    group_studentInfo.get<tgui::ListView>("ListView1")->onDoubleClick(&onItemDoubleClick, ref(group_studentInfo), ref(group_small_studentInfo), schoolYears);
    group_course.get<tgui::TreeView>("TreeView1")->onItemSelect(&onItemSelected2, ref(group_course), schoolYears, ref(curCourse2));
    group_course.get<Button>("Participants")->onClick(&onParticipants, ref(group_course), ref(curCourse2));
    group_student.get<tgui::Button>("ScoreBoard")->onClick(&onTeacherScoreboardSelected, ref(group_scoreboard), ref(group_student));
    group_student.get<tgui::Button>("Teacher Info")->onClick(&onStudentInfoSelected, ref(group_studentInfo), ref(group_student));
    group_student.get<tgui::Button>("Class ScoreBoard")->onClick(&onStudentInfoSelected, ref(group_studentSB), ref(group_student));
    group_student.get<tgui::Button>("Create")->onClick(&onCreateSelected, ref(group_create), ref(group_student));
    group_create.get<tgui::Button>("Reload")->onClick(&onReloadSelected, ref(gui), teacherName);
    gui.get<Tabs>("Tabs1")->onTabSelect(&onTabSelected2, ref(gui), curSelectedTab, vc);
    gui.get<Button>("Logout")->onClick(&onClickedLogout, ref(gui));
    return true;
}

void updateTextSizeMainMenuTeacher(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    //gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of 
}

void loadWidgetsMainMenuTeacher(tgui::BackendGui& gui, int dm)
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
    // Date 
    group_course.get<Label>("Date")->setVisible(false);
    group_course.get<Picture>("Picture3")->setVisible(false);
    group_course.get<TextArea>("TextArea2")->setVisible(false);

    group_course.get<Picture>("Picture1")->setVisible(false);
    group_course.get<Picture>("Picture2")->setVisible(false);
    group_course.get<Picture>("Picture4")->setVisible(false);

    group_course.get<TextArea>("TextArea1")->setVisible(false);
    group_course.get<Button>("Participants")->setVisible(false);
    group_course.get<ListView>("PaList")->setVisible(false);
}

void hideGroupSmallStudentInfo(Group& group_info)
{
    group_info.get<Button>("UpdateInformation")->setVisible(true);
    group_info.get<Button>("ChangePassword")->setVisible(false);
    group_info.get<Label>("CurrentPassword")->setVisible(false);
    group_info.get<Label>("InfoUpdate")->setVisible(false);
    group_info.get<Label>("NewPassword")->setVisible(false);
    group_info.get<Label>("ConfirmPassword")->setVisible(false);
    group_info.get<EditBox>("GetCur")->setVisible(false);
    group_info.get<EditBox>("GetNew")->setVisible(false);
    group_info.get<EditBox>("GetConfirm")->setVisible(false);
    group_info.get<EditBox>("StudentIDBox")->setReadOnly(false);
    group_info.get<EditBox>("FirstNameBox")->setReadOnly(false);
    group_info.get<EditBox>("LastNameBox")->setReadOnly(false);
    group_info.get<EditBox>("GenderBox")->setReadOnly(false);
    group_info.get<EditBox>("SocialIDBox")->setReadOnly(false);
    group_info.get<EditBox>("DoBBox")->setReadOnly(false);
    group_info.get<EditBox>("CreditBox")->setReadOnly(false);
}

void run_mainmenu_teacher(BackendGui& gui, tgui::String teacherName, int dm)
{
    loadWidgetsMainMenuTeacher(gui, dm);
    auto group_course = tgui::Group::create();
    auto group_student = tgui::Group::create();
    auto group_scoreboard = tgui::Group::create();
    auto group_studentInfo = tgui::Group::create();
    auto group_create = tgui::Group::create();
    auto group_small_studentInfo = tgui::Group::create();
    auto group_studentSB = tgui::Group::create();

    if (true)
    {
        group_student->loadWidgetsFromFile("TeacherInformationForm.txt");
        group_course->loadWidgetsFromFile("CourseInformationForm.txt");
        group_scoreboard->loadWidgetsFromFile("TeacherScoreboardForm.txt");
        group_small_studentInfo->loadWidgetsFromFile("StudentInfoForm.txt");
    }
    SchoolYear* schoolYears = nullptr;
    loadListofSchoolYears(schoolYears);
    addComponents2(gui, schoolYears, teacherName, *group_course, *group_student, *group_scoreboard, *group_studentSB, *group_studentInfo, *group_small_studentInfo, *group_create);
    gui.add(group_course);
    gui.add(group_student);
    gui.add(group_scoreboard);
    gui.add(group_studentInfo);
    gui.add(group_create);
    gui.add(group_small_studentInfo);
    gui.add(group_studentSB);
    group_course->setVisible(true);
    group_student->setVisible(false);
    group_scoreboard->setVisible(false);
    group_studentInfo->setVisible(false);
    group_small_studentInfo->setVisible(false);
    group_create->setVisible(false);
    group_studentSB->setVisible(false);

    hideGroupCourseTeacher(ref(*group_course));
    hideGroupSmallStudentInfo(ref(*group_small_studentInfo));
}
