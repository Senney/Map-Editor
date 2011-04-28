#ifndef COMPONENT_H
#define COMPONENT_H

#include <sfml/Graphics.hpp>
#include <sfml/Window.hpp>

namespace SenGUI
{
	class PanelBase;
	class Component;

	typedef int (*handlerptr)(const sf::Input&, Component*);

	class Component
	{
	public:
		Component();

		virtual void SetSize(int width, int height);
		int GetWidth() { return cWidth; }
		int GetHeight() { return cHeight; }

		virtual void SetPosition(int x, int y);
		int GetX() { return cXPosition; }
		int GetY() { return cYPosition; }

		void SetBGColor(sf::Color bgColor) { color = bgColor; }
		sf::Color GetBGColor() { return color; }

		virtual void SetInputHandler(int (*handler)(const sf::Input&, Component*));
		virtual void Update(const sf::Input& input);
		
		virtual sf::Image& GetImage() { return componentImage; }

		virtual void SetParent(PanelBase* parentPanel);
		PanelBase* GetParent() { return parent; }

	protected:
		sf::Color color;
		int cWidth, cHeight;
		int cXPosition, cYPosition;

		sf::Image componentImage;		

	private:
		virtual void UpdateImage();

		PanelBase* parent;

		bool hasHandler;
		handlerptr inputHandler;
	};
}

#endif