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
    accountText.setPosition(0.f, 0.f);
    accountText.setFillColor(Color::Red);
    accountText.setFont(font);
    accountText.setCharacterSize(10);
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
}

void LoginState::update()
{
    this->updateMousePositions();
    this->updateKeyBinds();

}

void LoginState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
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


