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
    this->buttons["LOGIN_BUTTON"] = new Button(300, 480, 450, 50, &this->font, "LOGIN", Color(100, 100, 100, 100)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200)); 
    this->account = new Textbox(300, 300, 450, 50, 20 , Color::Red, false, &this->font);
    this->password = new Textbox(300, 360 , 450, 50, 20, Color::Red, false, &this->font);


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
    this->account->update(mousePosView); 
    this->password->update(mousePosView);
    cout << mousePosView.x << ' ' << mousePosView.y << endl; 
    Event e; 
    while (this->app->pollEvent(e))
    {
        if (e.type == Event::TextEntered)
        {
            if (this->account->isChoosed())
            {
                if (Keyboard::isKeyPressed(Keyboard::Return))
                    this->account->setSelected(false);
                else
                    this->account->typedOn(e);
            }
            if (this->password->isChoosed())
            {
                if (Keyboard::isKeyPressed(Keyboard::Return))
                    this->password->setSelected(false);
                else
                    this->password->typedOn(e);
            }
        }
    }
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
    this->account->drawTo(target); 
    this->password->drawTo(target);
    this->renderButtons(target);
}


