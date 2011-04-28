#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>

#include "Panel.h"
#include "Button.h"

class MapEditor
{
public:
	MapEditor();

	void Run();

	static sf::RenderWindow* GetWindow() { return windowInst; }

private:
	sf::RenderWindow* mWindow;
	static void SetWindowInstance(sf::RenderWindow* inst) { windowInst = inst; }
	SenGUI::Panel mainPanel;
	SenGUI::Button testButton;

	static sf::RenderWindow* windowInst;

	// Button handlers
	static int CloseWindow(const sf::Input& input, SenGUI::Component* caller);

};

#endif