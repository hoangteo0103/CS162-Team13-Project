#include "Core.h"
void Core::initWindow()
{
	string title = "test"; 
	VideoMode Size(1000, 1000); 
	this->app = new RenderWindow(Size, title); 
}

void Core::initStates()
{
	this->states.push(new LoginState(this->app, &this->states)); 
}

Core::Core()
{
	this->initWindow();
	this->initStates(); 
}

Core::~Core()
{
	delete this->app;

}

void Core::endApplication()
{
	cout << "Ending Apllication" << endl; 
}

void Core::updateSFMLEvents()
{
	while (this->app->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == Event::Closed)
			this->app->close(); 
	}
}

void Core::update()
{
	this->updateSFMLEvents(); 
	if (!this->states.empty())
	{
		this->states.top()->update();
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop(); 
		}
	}
}

void Core::render()
{
	this->app->clear();
	if (!this->states.empty())
		this->states.top()->render(); 
	else 
	{
		this->endApplication();
		this->app->close();
	}
	this->app->display();
}

void Core::run()
{
	while (this->app->isOpen())
	{
		this->update();
		this->render(); 
	}
}