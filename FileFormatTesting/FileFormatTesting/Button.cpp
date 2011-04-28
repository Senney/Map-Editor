#include "Button.h"
using namespace SenGUI;

Button::Button() {}

void Button::UpdateImage()
{
	componentImage = sf::Image(cWidth, cHeight, color);
}

bool Button::IsClicked(int mouseX, int mouseY)
{
	return (mouseX > cXPosition && mouseX < (cXPosition + cWidth) &&
		mouseY > cYPosition && mouseY < (cYPosition + cHeight));
}