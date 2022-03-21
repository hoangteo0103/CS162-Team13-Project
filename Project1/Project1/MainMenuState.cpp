#include "MainMenuState.h"

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("raleway.ttf"))
    {

    }

    t.loadFromFile("images/mainmenu.png");
    this->background.setTexture(t);
}
void MainMenuState::initButtons()
{

}
MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->buttons["ADD_SCHOOL_YEAR_BUTTON"] = new Button(300, 480, 450, 50, &this->font, "ADD SCHOOL YEAR", Color(100, 100, 100, 100)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200));
    nowClass = nullptr;
    loadListofSpecificClasses(nowClass);
    for (SpecificClass* cur = nowClass; cur != NULL; cur = cur->nextClass)
    {
        cout << 1; 
        cur->outputToScreenClassInfo(); 
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

void MainMenuState::addSpecificCLass(SpecificClass*& nowClass, char classCode[NAMELENGTH])
{
    SpecificClass* newClass = new SpecificClass;
    newClass->changeClassCode( classCode ) ;
    newClass->inputFileClassInfo();
    if (nowClass == NULL)
    {
        nowClass = newClass; 
        return; 
    }
    newClass->nextClass = nowClass; 
    nowClass = newClass; 
}

void MainMenuState::loadListofSpecificClasses(SpecificClass*& nowClass)
{
    ifstream fin ("SchoolYears/Year2021-2022/SpecificClasses/ListOfClassCode.txt") ;
    char classCode[NAMELENGTH]; 
    while (fin.get(classCode, NAMELENGTH, '\n'))
    {
        addSpecificCLass(nowClass, classCode);
    }
}

void MainMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["ADD_SCHOOL_YEAR_BUTTON"]->isPressed())
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

    //target->draw(this->background);
    this->renderButtons(target);
}


