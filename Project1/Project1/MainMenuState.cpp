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
    this->werePressed = false;
    this->buttons["CREATE_SCHOOL_YEAR"] = new Button(300, 480, 450, 50, &this->font, "Create School Year", Color(100, 100, 100, 100)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200));
    this->textboxes["SCHOOL_YEAR"] = new Textbox(300, 600, 450, 50, 20, Color::Red, false, &this->font);
}
MainMenuState ::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    for (auto tmp = this->textboxes.begin(); tmp != this->textboxes.end(); ++tmp) {
        delete tmp->second;
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
void MainMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["CREATE_SCHOOL_YEAR"]->isPressed())
    {
        this->werePressed = true;
    }
}

void MainMenuState::updateTextBoxes() {
    if (!this->werePressed) return;
    for (auto& i : this->textboxes) {
        i.second->update(this->mousePosView);
    }
}

void MainMenuState::update(sf::Event *event)
{
    this->updateButtons();
    this->updateTextBoxes();
    this->updateMousePositions();
    this->updateKeyBinds();

    if (!this->werePressed) return;

    Event e;
    if (event) e = *event;
    if (event && e.type == Event::TextEntered) {
        for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++) {
            if (i->second->isChoosed()) {
                if (Keyboard::isKeyPressed(Keyboard::Return))
                    i->second->setSelected(false);
                else
                    i->second->typedOn(e);
            }
        }
    }
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
    target->clear(Color::White);
    target->draw(this->background);
    this->renderButtons(target);
    if (!this->werePressed) return;
    for (auto& i : this->textboxes) {
        i.second->drawTo(target);
    }
}


