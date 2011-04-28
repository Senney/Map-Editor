#include "Component.h"

using namespace SenGUI;

Component::Component()
{
	cXPosition = cYPosition = cWidth = cHeight = 0;
	color = sf::Color(0, 0, 0);
	hasHandler = false;
	UpdateImage();
}

void Component::SetSize(int width, int height)
{
	cWidth = width;
	cHeight = height;

	UpdateImage();
}

void Component::SetPosition(int x, int y)
{
	cXPosition = x;
	cYPosition = y;

	UpdateImage();
}

void Component::SetInputHandler(int (handler)(const sf::Input&, Component*))
{
	hasHandler = true;
	inputHandler = handler;
}

void Component::Update(const sf::Input& input)
{
	if (hasHandler)
		inputHandler(input, this);
}

void Component::UpdateImage()
{
	// Empty for base component.
}

void Component::SetParent(PanelBase* parentPanel)
{
	parent = parentPanel;
}