#ifndef PANELBASE_H
#define PANELBASE_H

#include <vector>

#include <sfml/Graphics.hpp>

#define DEFAULT_PANEL_SIZE 30

class MapEditor;

namespace SenGUI
{
	class Component;

	class PanelBase : public sf::Drawable
	{
	public:
		PanelBase();

		virtual void SetSize(int width, int height);
		int GetWidth() { return pWidth; }
		int GetHeight() { return pHeight; }

		void SetBGColor(sf::Color bgColor) { color = bgColor; }
		sf::Color GetBGColor() { return color; }

		sf::Image& GetImageBuffer() { return buffer; }

		virtual void AddComponent(Component src);
		virtual void UpdateComponents();

		void SetVisible(bool visible) { isShowing = visible; }
		bool GetVisible() { return isShowing; }

	private:
		virtual void Render(sf::RenderTarget& Target) const;
		void UpdatePanel();

		bool isShowing;

		std::vector<Component> components;
		sf::Color color;
		sf::Image buffer;
		sf::Sprite panelSprite;
		int pHeight, pWidth;

	};
}

#endif