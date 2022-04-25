#include "State.h"
State::State(RenderWindow* app, stack<State*>* states)
{
    this->app = app;
    this->states = states;
    this->quit = false;
    this->paused = false;
}
State::~State()
{
}
void State::updateMousePositions()
{
    this->mousePosWindow = Mouse::getPosition(*this->app);
    this->mousePosView = this->app->mapPixelToCoords(Mouse::getPosition(*this->app));
}
const bool& State::getQuit() const
{
    return this->quit;
}
void State::checkForQuit()
{
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        this->quit = true;
    }
}

