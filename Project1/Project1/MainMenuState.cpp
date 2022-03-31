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

void onTabSelected(tgui::BackendGui& gui, tgui::String selectedTab)
{  
    if (selectedTab == "Semester 1") {
        gui.get("Courses1")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    }
    else
    {
        gui.get("Courses1")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
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

    auto tabs = tgui::Tabs::create();
    tabs->setRenderer(theme.getRenderer("Tabs"));
    tabs->setTabHeight(30);
    tabs->setPosition(10, 40);
    tabs->add("Semester 1");
    tabs->add("Semester 2");
    tabs->add("Semester 3");

    gui.add(tabs);

    tgui::String className;

    SchoolYear* curSchoolYear = nullptr;

    for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        if (i->nowClass->findStudent(studentID.toStdString())) {
            curSchoolYear = i;
            tgui::String t = tgui::String(i->startYear) + "-" + tgui::String(i->endYear);
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
    for (Semester* i = curSchoolYear->nowSemester; i; i = i->nextSemester) {
        for (Course* j = i->nowCourse; j; j = j->nextCourse) {
            tgui::String item = j->courseName;
            listBox->addItem(item);
        }

        //tgui::String item = "Item " + tgui::String(i);
        //listBox->addItem(item);
        //gui.add(label);
        //auto pic = tgui::Picture::create("Image" + tgui::String(i + 1) + ".png");
        //pic->setSize(400, 300);
        //pic->setPosition(0, i * 300);
        
    }

    //tabs->select("Semester 1");
    gui.add(listBox, "Courses1");  
    listBox->setPosition({ tgui::bindLeft(tabs), tgui::bindBottom(tabs) });
    tabs->onTabSelect(&onTabSelected, ref(gui));

    // The scrollable area / content size is now 400x900 because of the pictures inside it.
    // If you wish to manually specify the size then you can call the setContentSize function.

    // Hide the horizontal scrollbar. Since the pictures have the same width as the panel,
    // the pictures won't fit inside the panel anymore when the vertical scrollbar is visible.
    // Note that by removing the horizontal scrollbar you won't be able to see the small part
    // of the picture that ends up below the vertical scrollbar.
    //panel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    return true;
}

void updateTextSizeMainMenu(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of height
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
    /*for (SchoolYear* i = schoolYears; i != nullptr; i = i->nextSchoolYear) {
        i->outputClassedInfo();
    }*/
    
    addComponents(gui, schoolYears, studentID);
    //runExample(gui);
}

