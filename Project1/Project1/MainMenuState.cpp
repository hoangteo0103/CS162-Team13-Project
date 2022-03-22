#include "MainMenuState.h"

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("raleway.ttf"))
    {

    }

    t.loadFromFile("images/KHTN.png");
    this->background.setTexture(t);
}
void MainMenuState::initButtons()
{

}
MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->buttons["SEE_COURSES"] = new Button(300, 700, 450, 50, &this->font, "See enrolled courses", Color(100, 100, 100, 100)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200));
    nowClass = nullptr;
    loadListofSchoolYears(this->schoolYear);
    //loadListofSpecificClasses(this->nowClass);
    for (SchoolYear* cur = this->schoolYear; cur != nullptr; cur = cur->nextSchoolYear)
    { 
        cur->outputClassedInfo();
    }
}
MainMenuState ::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}
void MainMenuState::updateKeyBinds()
{
    this->checkForQuit();
}
void MainMenuState::endState()
{
    cout << "End MainMenu" << endl;
}

//void MainMenuState::addSpecificCLass(SpecificClass*& nowClass, char classCode[])
//{
//    SpecificClass* newClass = new SpecificClass;
//    newClass->changeClassCode(classCode);
//    //cerr << classCode << '\n';
//    //system("pause");
//    newClass->inputFileClassInfo();
//    //newClass->outputToScreenClassInfo();
//    if (nowClass == NULL)
//    {
//        
//        nowClass = newClass; 
//        return; 
//    }
//    newClass->nextClass = nowClass; 
//    nowClass = newClass; 
//}

void MainMenuState::loadListofSchoolYears(SchoolYear*& schoolYear) {
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

        SchoolYear* tmp = new SchoolYear(yearStart, yearEnd);
        tmp->loadListofSpecificClasses(year);

        if (!schoolYear) {
            schoolYear = tmp;
        }
        else {
            tmp->nextSchoolYear = schoolYear;
            schoolYear = tmp;
        }
    }
    yearInput.close();
}

//void MainMenuState::loadListofSpecificClasses(SpecificClass*& nowClass, string year)
//{
//	ifstream fin("SchoolYears/" + year + "/ListOfClassCode.txt");
//	char classCode[NAMELENGTH];
//	while (fin.get(classCode, NAMELENGTH, '\n'))
//	{
//		addSpecificCLass(nowClass, classCode);
//	}
//}

void MainMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["SEE_COURSES"]->isPressed())
    {
        //schoolYear->addFirstYearClass();
        cout << "OK"; 
    }
}

void MainMenuState::update(sf::Event *event)
{
    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();
    //system("cls") ;
    //cout << mousePosView.x <<' ' << mousePosView.y <<endl;

}
void MainMenuState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void MainMenuState::render(RenderTarget* target)
{
    if (!target)
        target = this->app;

    target->draw(this->background);
    this->renderButtons(target);
}


