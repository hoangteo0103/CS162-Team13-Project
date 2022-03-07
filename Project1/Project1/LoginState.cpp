#include "LoginState.h"


void LoginState::initFonts()
{
    if (!this->font.loadFromFile("raleway.ttf"))
    {

    }
    textureLogo.loadFromFile("logo.png");
    this->logoImage.setTexture(textureLogo);
}
LoginState::LoginState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->logoImage.setPosition(0.f, 0.f);
    this->buttons["LOGIN_BUTTON"] = new Button(300, 600, 450, 50, &this->font, "LOGIN", Color(100, 100, 100, 100)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200)); 
}

LoginState ::~LoginState()
{
    //delete this->pmenu;
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}


void LoginState::updateKeyBinds()
{
    this->checkForQuit();
}

void LoginState::endState()
{
    this->quit = true;
    cout << "End MainMenu" << endl;
}


void LoginState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["LOGIN_BUTTON"]->isPressed())
    {
        //cout << 1; 
    }
}

void LoginState::update()
{
    this->updateButtons();
    this->updateMousePositions();
    this->updateKeyBinds();
    cout << mousePosView.x << ' ' << mousePosView.y << endl; 

}

void LoginState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        //cout << 1 << endl; 
        it.second->render(target);
    }
}

void LoginState::render(RenderTarget* target)
{
    if (this->quit)
        return;
    if (!target)
        target = this->app;
    target->clear(Color::White);
    target->draw(this->logoImage);
    this->renderButtons(target);
}


