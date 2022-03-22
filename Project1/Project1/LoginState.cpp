
#include "LoginState.h"

void LoginState::initFonts()
{
    if (!this->font.loadFromFile("raleway.ttf"))
    {

    }
    textureLogo.loadFromFile("logo.png");
    this->logoImage.setTexture(textureLogo);
    textureHeader.loadFromFile("headerlogo.png");
    this->headerlogoImage.setTexture(textureHeader);
}
LoginState::LoginState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->logoImage.setPosition(0.f, 0.f);
    this->headerlogoImage.setPosition(300.f, 170.f);
    //this->headerlogoImage.setScale(100, 100); 
    this->buttons["LOGIN_BUTTON"] = new Button(300, 480, 450, 50, &this->font, "LOGIN", Color(100, 100, 100, 100)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200)); 
    this->loginText["ACCOUNT"] = new Textbox(300, 300, 450, 50, 20, Color::Red, false, &this->font);
    this->loginText["PASSWORD"] = new Textbox(300, 360, 450, 50, 20, Color::Red, false, &this->font);

    this->wrongPassText.setFont(this->font);
    this->wrongPassText.setFillColor(Color::Red); 
    this->wrongPassText.setCharacterSize(20);
    this->wrongPassText.setPosition(Vector2f(300, 430));
    this->wrongPassText.setString("sai mat khau roi em oi");
    loadAccount();
}

LoginState ::~LoginState()
{
    //delete this->pmenu;
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    for (auto it = this->loginText.begin(); it != this->loginText.end(); ++it) {
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
       this->wrongPass = false;
       std::string tmpAccount = loginText["ACCOUNT"]->getText();
       std::string tmpPassword = loginText["PASSWORD"]->getText();
       bool check = checkLoginAcc(tmpAccount, tmpPassword);
       cout << check << endl;
       if (check)
       {
           this->states->push(new MainMenuState(this->app, this->states));
       }
       else {
           this->wrongPass = true; 
       }
    }
    cout << this->wrongPass; 
}

void LoginState::updateLoginText() {
    //int cnt = 0;
    //for (auto i : this->loginText) {
    //    //cout << "Update for the " << cnt << " time\n";
    //    //cout << "Here is the mousePos : " << mousePosView.x << ' ' << mousePosView.y << '\n';
    //    //system("pause");
    //    i.second->update(this->mousePosView);
    //}

    for (auto& i : this->loginText) {
        i.second->update(this->mousePosView);
    }
}

void LoginState::update(sf::Event* event)
{
    this->updateButtons();
    this->updateLoginText();
    this->updateMousePositions();
    this->updateKeyBinds();
    //this->account->update(mousePosView); 
    //this->password->update(mousePosView);
    system("cls");
    cout << mousePosView.x << ' ' << mousePosView.y << endl;
    Event e;
    if (event) e = *event;
	if (event && e.type == Event::TextEntered) {
        //cerr << "Yeah I was here u know\n";
		for (auto i = this->loginText.begin(); i != this->loginText.end(); i++) {
			if (i->second->isChoosed()) {
				if (Keyboard::isKeyPressed(Keyboard::Return))
					i->second->setSelected(false);
				else
					i->second->typedOn(e);
			}
		}
	}

	/*if (e.type == Event::TextEntered)
	{
		if (this->loginText["ACCOUNT"]->isChoosed())
		{
			if (Keyboard::isKeyPressed(Keyboard::Return))
				this->loginText["ACCOUNT"]->setSelected(false);
			else
				this->loginText["ACCOUNT"]->typedOn(e);
		}
		if (this->loginText["PASSWORD"]->isChoosed())
		{
			if (Keyboard::isKeyPressed(Keyboard::Return))
				this->loginText["PASSWORD"]->setSelected(false);
			else
				this->loginText["PASSWORD"]->typedOn(e);
		}
	}*/
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
    target->draw(this->headerlogoImage);
    for (auto& i : this->loginText) {
        i.second->drawTo(target);
    }
    this->renderButtons(target);
    if(this->wrongPass) target->draw(this->wrongPassText);
}

void LoginState::loadAccount() {
    ifstream fin1;
    fin1.open("Account.txt");
    ifstream fin2;
    fin2.open("Password.txt");
    while (!fin1.eof()) {
        std::string tmpAcc, tmpPwrd;
        fin1 >> tmpAcc; fin2 >> tmpPwrd;
        addAccount(this->listHead, this->listLast, tmpAcc, tmpPwrd);
    }
    fin1.close(); fin2.close();
}

bool LoginState::checkLoginAcc(std::string accnt, std::string psswrd) {
    for (Account* i = this->listHead; i; i = i->nextStudent) {
        if (!(i->accnt.compare(accnt)) && !(i->psswrd.compare(psswrd))) {
            delList(this->listHead);
            this->listHead = this->listLast = nullptr;
            return true;
        }
    }
    return false;
}