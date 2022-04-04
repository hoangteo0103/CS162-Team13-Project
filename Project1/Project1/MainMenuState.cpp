//#include "MainMenuState.h"
//
//void MainMenuState::initFonts()
//{
//    if (!this->font.loadFromFile("raleway.ttf"))
//    {
//
//    }
//
//    t.loadFromFile("images/KHTN.png");
//    this->background.setTexture(t);
//}
//void MainMenuState::initButtons()
//{
//
//}
//MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states, std::string sID)
//    :State(app, states)
//{
//    this->curStudentID = sID;
//    this->initFonts();
//    this->buttons["SEE_COURSES"] = new Button(450, 700, 450, 50, &this->font, "See enrolled courses", Color(100, 100, 100, 100)
//        , Color(10, 10, 10, 10), Color(20, 20, 20, 200));
//    nowClass = nullptr;
//    loadListofSchoolYears(this->schoolYear);
//    //loadListofSpecificClasses(this->nowClass);
//    for (SchoolYear* cur = this->schoolYear; cur != nullptr; cur = cur->nextSchoolYear)
//    { 
//        //cur->outputClassedInfo();
//    }
//}
//MainMenuState ::~MainMenuState()
//{
//    auto it = this->buttons.begin();
//    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
//    {
//        delete it->second;
//    }
//}
//void MainMenuState::updateKeyBinds()
//{
//    this->checkForQuit();
//}
//void MainMenuState::endState()
//{
//    cout << "End MainMenu" << endl;
//}
//
//
//

//void MainMenuState::updateButtons()
//{
//    for (auto& it : this->buttons)
//    {
//        it.second->update(this->mousePosView);
//    }
//    if (this->buttons["SEE_COURSES"]->isPressed())
//    {
//        //schoolYear->addFirstYearClass();
//        cout << "OK"; 
//    }
//}
//
//void MainMenuState::update(sf::Event *event)
//{
//    this->updateMousePositions();
//    this->updateKeyBinds();
//    this->updateButtons();
//    //system("cls") ;
//    //cout << mousePosView.x <<' ' << mousePosView.y <<endl;
//
//}
//void MainMenuState::renderButtons(RenderTarget* target)
//{
//    for (auto& it : this->buttons)
//    {
//        it.second->render(target);
//    }
//}
//void MainMenuState::render(RenderTarget* target)
//{
//    if (!target)
//        target = this->app;
//
//    target->draw(this->background);
//    this->renderButtons(target);
//}
//
//
#include "MainMenuState.h"

void hideCoursesInfo(tgui::BackendGui& gui) {
    gui.get<ScrollablePanel>("ScrollablePanel1")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<tgui::TreeView>("TreeView1")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
}

void hideStudentInfo(tgui::BackendGui& gui) {
    gui.get<Button>("Student Info")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("Course Registration")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("ScoreBoard")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("Button1")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
}

void showStudentInfo(tgui::BackendGui& gui) {
    gui.get<Button>("Student Info")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("Course Registration")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("ScoreBoard")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("Button1")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
}

void showCoursesInfo(tgui::BackendGui& gui) {
    gui.get<ScrollablePanel>("ScrollablePanel1")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<tgui::TreeView>("TreeView1")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
}

void onTabSelected(tgui::BackendGui& gui, tgui::String* curSelectedTab, tgui::String selectedTab)
{
    //cerr << *curSelectedTab << '\n';
    //cerr << selectedTab << '\n';

    if (*curSelectedTab == tgui::String("Courses Information")) {
        hideCoursesInfo(gui);
    }
    else if (*curSelectedTab == tgui::String("Student Information")) {
        hideStudentInfo(gui);
    }

    if (selectedTab == tgui::String("Courses Information")) {
        *curSelectedTab = tgui::String("Courses Information");
        showCoursesInfo(gui);
    }
    else if (selectedTab == tgui::String("Student Information"))
    {
        *curSelectedTab = tgui::String("Student Information");
        //cerr << *curSelectedTab << '\n';
        showStudentInfo(gui);
    }
}

void onItemSelected(tgui::BackendGui& gui, SchoolYear* schoolYears, tgui::String selectedItem) {
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
        gui.get<tgui::ScrollablePanel>("ScrollablePanel1")->add(tArea, "TArea");
    }
    else {
        gui.get<tgui::ScrollablePanel>("ScrollablePanel1")->removeAllWidgets();
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
        addSpecificClass(nowClass, classCode, year);
    }
}

bool addComponents(tgui::BackendGui& gui, SchoolYear*& schoolYears, tgui::String studentID)
{
    tgui::Theme theme{ "themes/Black.txt" };

    auto label = tgui::Label::create();
    label->setRenderer(theme.getRenderer("Label"));

    //gui.get<tgui::TreeView>("TreeView1")->addItem({ "This", "Is", "Similar" });
    //gui.get<tgui::TreeView>("TreeView1")->addItem({ "This", "Tree" });

    tgui::String className;

    SchoolYear* curSchoolYear = nullptr;

    for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        string studentName;

        tgui::String years = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);
        gui.get<tgui::TreeView>("TreeView1")->addItem({ years });

        if (i->nowClass->findStudent(studentID.toStdString(), studentName)) {
            curSchoolYear = i;
            tgui::String t = studentName;
            label->setText(t);
        }
    }

    label->setPosition(10, 10);
    label->setTextSize(20);
    gui.add(label);

    /*auto panel = tgui::ScrollablePanel::create();
    panel->setPosition(100, 50);
    panel->setSize(400, 500);
    *///gui.add(panel);

    auto listBox = tgui::ListBox::create();
    listBox->setRenderer(theme.getRenderer("ListBox"));
    listBox->setSize(400, 300);
    listBox->setItemHeight(50);
    listBox->setPosition(10, 100);

    // Create some pictures to place inside the scrollable panel
    if (!curSchoolYear) return false;

    tgui::String curYears = tgui::String(curSchoolYear->startYear) + '-' + tgui::String(curSchoolYear->endYear);

    int curSemester = 4;

    tgui::String curDirectory = "SchoolYears/" + tgui::String(curSchoolYear->startYear) + "-" + tgui::String(curSchoolYear->endYear);

    for (Semester* i = curSchoolYear->nowSemester; i; i = i->nextSemester) {
        curSemester--;
        tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
        string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
        //cerr << curDir << '\n';
        gui.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr });
        for (Course* j = i->nowCourse; j; j = j->nextCourse) {
            if (j->findStudent(curDir, studentID.toStdString())) {
                //cerr << 1 << '\n';
                tgui::String item = j->courseName;
                listBox->addItem(item);
                gui.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr, item });
            }
        }

    }

    gui.get<Tabs>("Tabs1")->select("Courses Information");
    tgui::String* curSelectedTab = new tgui::String;
    *curSelectedTab = "Courses Information";
    
    listBox->setPosition({ tgui::bindLeft(gui.get<Tabs>("Tabs1")), tgui::bindBottom(gui.get<Tabs>("Tabs1")) });
    gui.get<Tabs>("Tabs1")->onTabSelect(&onTabSelected, ref(gui), curSelectedTab);
    gui.get<tgui::TreeView>("TreeView1")->onItemSelect(&onItemSelected, ref(gui), schoolYears);

    return true;
}

void updateTextSizeMainMenu(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of height
    gui.get<Button>("Student Info")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("Course Registration")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("ScoreBoard")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<Button>("Button1")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));

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
    SchoolYear* schoolYears = nullptr;
    loadListofSchoolYears(schoolYears);
    addComponents(gui, schoolYears, studentID);
}