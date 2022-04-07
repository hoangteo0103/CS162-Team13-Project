#include "MainMenuState.h"      

void onTabSelected(tgui::BackendGui& gui, tgui::String* curSelectedTab, vector<tgui::Group*>* vc,  tgui::String selectedTab)
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

    for (int i = 0; i < 3; i++)
    {
        (*vc)[i]->setVisible(false);
    }
    
   //(*vc)[1] = 5;
   (*vc)[selectedIndex]->setVisible(true);
}

void onItemSelected(tgui::Group& group_course, SchoolYear* schoolYears, tgui::String selectedItem) {
    string sItem = selectedItem.toStdString();
    bool check = false;
    auto tArea = tgui::TextArea::create();
    tArea->setSize(600, 450);
    tArea->setReadOnly();
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

        //cerr << year << '\n';

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

bool addComponents(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String studentID, tgui::Group& group_course, tgui::Group& group_student, tgui::Group& group_scoreboard)
{

    tgui::Theme theme{ "themes/Black.txt" };

    auto label = tgui::Label::create();
    label->setRenderer(theme.getRenderer("Label"));
    label->setSize(500, 500);
    label->setPosition(1100, 10);
    label->setTextSize(20);

    tgui::String className;

    queue<pair<SchoolYear*, int>> curSchoolYear;

    string studentName;

    for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        bool findCheck = false;

        //tgui::String years = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

        for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
            if (j->findStudent(studentID.toStdString(), studentName)) {
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
    loadwidget(group_scoreboard, curSchoolYear);
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

    group_course.get<tgui::TreeView>("TreeView1")->onItemSelect(&onItemSelected, ref(group_course), schoolYears);
    group_student.get<tgui::Button>("ScoreBoard")->onClick(&onScoreboardSelected, ref(group_scoreboard), ref(group_student));
    gui.get<Tabs>("Tabs1")->onTabSelect(&onTabSelected, ref(gui), curSelectedTab, vc);

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

void run_mainmenu(BackendGui& gui, tgui::String studentID)
{
    loadWidgetsMainMenu(gui);
    auto group_course = tgui::Group::create();
    auto group_student = tgui::Group::create();
    auto group_scoreboard = tgui::Group::create();
    group_student->loadWidgetsFromFile("StudentInformationForm.txt");
    group_course->loadWidgetsFromFile("CourseInformationForm.txt");
    SchoolYear* schoolYears = nullptr;
    loadListofSchoolYears(schoolYears);
    addComponents(gui, schoolYears, studentID, *group_course, *group_student, *group_scoreboard);
    gui.add(group_course);
    gui.add(group_student);
    gui.add(group_scoreboard);
    group_course->setVisible(true);
    group_student->setVisible(false);
    group_scoreboard->setVisible(false);
}