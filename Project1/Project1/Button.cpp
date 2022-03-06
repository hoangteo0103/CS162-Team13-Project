#include "Button.h"

Button::Button(float x, float y, float width, float height, Font* font,
    string text, Color idleColor, Color hoverColor, Color activeColor)
{
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(Vector2f(x, y));
    this->shape.setSize(Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(Color::White);
    this->text.setCharacterSize(12);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->shape.setFillColor(this->idleColor);
}
Button::~Button()
{

}
void Button::setOutline(Color  color)
{
    this->shape.setOutlineColor(Color::Red);
}
void Button::updateText(string t)
{
    this->text.setString(t);
}
void Button::update(const Vector2f mousePos)
{
    //IDLE
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        //HOVER
        this->buttonState = BTN_HOVER;
        bool leftPress = false;
        while (Mouse::isButtonPressed(Mouse::Left))
        {
            leftPress = true;
        }
        if (leftPress)  this->buttonState = BTN_ACTIVE;
    }
    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    default:
        this->shape.setFillColor(Color::Red);
        break;
    }
}
const bool Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}
void Button::render(RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}


