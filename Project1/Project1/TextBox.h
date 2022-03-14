#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std; 
using namespace sf;

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
private:
	Text textbox;
	RectangleShape shape; 
	ostringstream text;
	bool hasLimit = false;
	int limit = 0;
	bool isClicked  = false , isSelected = false  ; 
	// Delete the last character of the text:
	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_");
	}

	// Get user input:
	void inputLogic(int charTyped) {
		// If the key pressed isn't delete, or the two selection keys, then append the text with the char:
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			text << static_cast<char>(charTyped);
		}
		// If the key is delete, then delete the char:
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		// Set the textbox text:
		textbox.setString(text.str() + "_");
	}
public:
	Textbox(int x , int y , int width , int height ,int size, Color color, bool sel , Font *fonts) {
		shape.setPosition(Vector2f(x, y));
		shape.setSize(Vector2f(width, height));
		shape.setFillColor(Color::Red); 
		textbox.setCharacterSize(size);
		textbox.setFillColor(Color::Black);
		textbox.setFont(*fonts); 
		isClicked = sel;

		// Check if the textbox is selected upon creation and display it accordingly:
		if (isClicked)
			textbox.setString("_");
		else
			textbox.setString("");
		textbox.setPosition(
			shape.getPosition().x + 5,
			shape.getPosition().y + height/2 - 2 
		);
	}

	// Set char limits:
	

	// Change selected state:
	void update(const Vector2f mousePos)

	{
		isClicked = false;
		if (shape.getGlobalBounds().contains(mousePos))
		{
			bool leftPress = false;
			while (Mouse::isButtonPressed(Mouse::Left))
			{
				leftPress = true;
			}
			if (leftPress)  isClicked = true;
		}
		if(isClicked)
			setSelected(isClicked); 
	}
	void setSelected(bool sel) {
		isSelected = sel;

		// If not selected, remove the '_' at the end:
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}
	bool isChoosed()
	{
		return isSelected; 
	}

	string getText() {
		return text.str();
	}

	void drawTo(sf::RenderTarget* target) {
		target->draw(shape);
		target->draw(textbox);
	}

	// Function for event loop:
	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;

			// Only allow normal inputs:
			if (charTyped < 128) {
				if (hasLimit) {
					// If there's a limit, don't go over it:
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					// But allow for char deletions:
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				// If no limit exists, just run the function:
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
};
#endif