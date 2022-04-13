#include "MainMenuState.h"      

void addSpecificClass(SpecificClass*& nowclass, char classcode[], string year)
{
    SpecificClass* newClass = new SpecificClass;
    newClass->changeClassCode(classcode);
    //cerr << classcode << '\n';
    //system("pause");
    newClass->inputFileClassInfo(year);
    //newclass->outputtoscreenclassinfo();
    if (nowclass == nullptr)
    {
        nowclass = newClass;
        return;
    }
    newClass->nextClass = nowclass;
    nowclass = newClass;
}

void loadListofSchoolYears(SchoolYear*& schoolYear) {
    string year;
    ifstream yearInput("SchoolYears.txt");
    while (!yearInput.eof()) {
        yearInput >> year;

        bool check = false; //get constructor value for SchoolYear
        int yearStart = 0, yearEnd = 0;
        for (int i = 0; i < year.size(); i++) {
            if (year[i] == '-') { check = true; continue; }
            if (!check) { yearStart *= 10; yearStart += year[i] - '0'; }
            else { yearEnd *= 10; yearEnd += year[i] - '0'; }
        }

        //cerr << year << '\n'

        //cerr << "SchoolYears/" + year + "ListOfSemester.txt" << '\n';
        ifstream fin1("SchoolYears/" + year + "/ListOfSemester.txt");
        int amount;
        fin1 >> amount;
        fin1.close();

        //cerr << amount << '\n';

        SchoolYear* tmpYear = new SchoolYear(yearStart, yearEnd);
        tmpYear->loadListofSpecificClasses(year);
        //cerr << 1 << '\n';
        tmpYear->loadListofSemester(amount, year);

        if (!schoolYear) {
            schoolYear = tmpYear;
        }
        else {
            tmpYear->nextSchoolYear = schoolYear;
            schoolYear = tmpYear;
        }
    }
    yearInput.close();
}

void loadListofSpecificClasses(SpecificClass*& nowClass, string year)
{
    ifstream fin("SchoolYears/" + year + "/ListOfClassCode.txt");
    char classCode[NAMELENGTH];
    while (fin.get(classCode, NAMELENGTH, '\n'))
    {
        //cerr << classCode << '\n';
        addSpecificClass(nowClass, classCode, year);
    }
}

bool addComponents(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String studentID, tgui::Group& group_course,
    tgui::Group& group_student, tgui::Group& group_scoreboard, tgui::Group& group_studentInfo)
{

    tgui::Theme theme{ "themes/Black.txt" };

    auto label = tgui::Label::create();
    label->setRenderer(theme.getRenderer("Label"));
    label->setSize(150, 150);
    label->setPosition(1020, 10);
    label->setTextSize(20);

    tgui::String className;

    queue<pair<SchoolYear*, int>> curSchoolYear;

    string studentName;

    Student neededStudent  ;

    for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        bool findCheck = false;

        //tgui::String years = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

        for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
            if (j->findStudent(studentID.toStdString(), studentName, neededStudent)) {
                tgui::String t = studentName;
                label->setText(t);
                findCheck = true;
                //group_course.get<tgui::TreeView>("TreeView1")->addItem({ years });
                break;
            }
        }

        if (findCheck) break;
    }

    for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        tgui::String years = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

        //cerr << years << '\n';
        int ID;
        for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
            if (j->findStudentByName(studentName, ID)) {
                curSchoolYear.push(make_pair(i, ID));
                group_course.get<tgui::TreeView>("TreeView1")->addItem({ years });
                break;
            }
        }
    }

    group_course.add(label);

    // Create some pictures to place inside the scrollable panel
    loadwidget(group_scoreboard, curSchoolYear, studentName);
    loadInfoWidget(group_studentInfo, neededStudent);

    //cerr << group_studentInfo.get<tgui::Label>("Label1")->getText() << '\n';

    if (curSchoolYear.empty()) return false;

    while (!curSchoolYear.empty()) {

        SchoolYear* cSYear = curSchoolYear.front().first;
        int sID = curSchoolYear.front().second;
        curSchoolYear.pop();


        string strID = "";
        while (sID) {
            strID += (char)((sID % 10) + '0');
            sID /= 10;
        }
        reverse(strID.begin(), strID.end());

        tgui::String curYears = tgui::String(cSYear->startYear) + '-' + tgui::String(cSYear->endYear);

        //cerr << curYears << '\n';

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear);

        for (Semester* i = cSYear->nowSemester; i; i = i->nextSemester) {
            curSemester--;
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
            //cerr << curDir << '\n';
            group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr });
            for (Course* j = i->nowCourse; j; j = j->nextCourse) {


                if (j->findStudent(curDir, strID)) {
                    //cerr << 1 << '\n';
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
    group_course.get<Button>("Participants")->onClick(&onParticipants , ref(group_course) ,curCourse);
    group_course.get<tgui::TreeView>("TreeView1")->onItemSelect(&onItemSelected, ref(group_course), schoolYears , curCourse , neededStudent);
    group_student.get<tgui::Button>("ScoreBoard")->onClick(&onScoreboardSelected, ref(group_scoreboard), ref(group_student));
    group_student.get<tgui::Button>("Student Info")->onClick(&onStudentInfoSelected, ref(group_studentInfo), ref(group_student));
    gui.get<Tabs>("Tabs1")->onTabSelect(&onTabSelected, ref(gui), curSelectedTab, vc);
    gui.get<Button>("Logout")->onClick(&onClickedLogout, ref(gui));
    return true;
}

void updateTextSizeMainMenu(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of 
}

void loadWidgetsMainMenu(tgui::BackendGui& gui)
{
    gui.loadWidgetsFromFile("MainMenuForm.txt");

    // Specify an initial text size instead of using the default value
    updateTextSizeMainMenu(gui);

    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui] { updateTextSizeMainMenu(gui); });
    //gui.get<tgui::Button>("Button1")->onPress(&login, gui, gui.get<tgui::EditBox>("EditBox1"), gui.get<tgui::EditBox>("EditBox2"), std::ref(accounts));
}

void hideGroupCourse(Group& group_course)
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

void run_mainmenu(BackendGui& gui, tgui::String studentID)
{
    loadWidgetsMainMenu(gui);
    auto group_course = tgui::Group::create();
    auto group_student = tgui::Group::create();
    auto group_scoreboard = tgui::Group::create();
    auto group_studentInfo = tgui::Group::create();
    group_student->loadWidgetsFromFile("StudentInformationForm.txt");
    group_course->loadWidgetsFromFile("CourseInformationForm.txt");
    SchoolYear* schoolYears = nullptr;
    loadListofSchoolYears(schoolYears);
    addComponents(gui, schoolYears, studentID, *group_course, *group_student, *group_scoreboard, *group_studentInfo);
    gui.add(group_course);
    gui.add(group_student);
    gui.add(group_scoreboard);
    gui.add(group_studentInfo);
    group_course->setVisible(true);
    group_student->setVisible(false);
    group_scoreboard->setVisible(false);
    group_studentInfo->setVisible(false);
    hideGroupCourse(*group_course);
}
