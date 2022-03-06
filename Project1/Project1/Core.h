#pragma once
#ifndef CORE_H
#define CORE_H
#include <iostream>
#include<stack>
#include <SFML/Graphics.hpp>
#include "LoginState.h"
using namespace sf;
using namespace std;
class Core
{
private : 
	RenderWindow* app; 
	Event sfEvent;
	stack<State*> states;

	void initWindow();
	void initStates(); 
public :
	Core();
	virtual ~Core(); 
	void endApplication();
	void updateSFMLEvents(); 
	void update();
	void render();
	void run();
};

#endif // !1




