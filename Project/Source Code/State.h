#pragma once
#ifndef STATE_H
#define STATE_H
#include<iostream>
#include<stack>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf; 
class State
{
protected:
    stack<State*>* states;
    RenderWindow* app;
    bool paused;
    bool quit;
    Vector2i mousePosWindow;
    Vector2f mousePosView;

public:
    State(RenderWindow* app, stack<State*>* states);
    virtual ~State();
    // Functions
    const bool& getQuit() const;
    virtual void checkForQuit();
    virtual void updateKeyBinds() =  0;
    virtual void updateMousePositions();
    virtual void endState() = 0;
    virtual void update(sf::Event* event = nullptr) = 0;
    virtual void render(RenderTarget* target = nullptr) = 0;

};
#endif

