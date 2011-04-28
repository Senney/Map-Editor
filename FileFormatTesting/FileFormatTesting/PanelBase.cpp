#include "PanelBase.h"
#include "Component.h"
#include "MapEditor.h"

using namespace SenGUI;

PanelBase::PanelBase()
{
	color = sf::Color(204, 204, 204);
	pWidth = pHeight = DEFAULT_PANEL_SIZE;
}

void PanelBase::Render(sf::RenderTarget& Target) const
{
	if (!isShowing)
		return;

	Target.Draw(panelSprite);
}

void PanelBase::UpdatePanel()
{
	if (!isShowing)
		return;

	buffer = sf::Image(pWidth, pHeight, color);

	std::vector<Component>::iterator i = components.begin();
	for (; i != components.end(); i++)
	{
		int x = i->GetX();
		int y = i->GetY();
		sf::Image& srcimg = i->GetImage();

		// Add the image.
		buffer.Copy(srcimg, x, y);
	}

	panelSprite.SetImage(buffer);
}

void PanelBase::SetSize(int width, int height)
{
	pWidth = width;
	pHeight = height;

	UpdatePanel();
}

void PanelBase::AddComponent(Component src)
{
	src.SetParent(this);
	components.push_back(src);

	UpdatePanel();
}

void PanelBase::UpdateComponents()
{
	if (!isShowing)
		return;

	const sf::Input& input = MapEditor::GetWindow()->GetInput();
	std::vector<Component>::iterator i = components.begin();
	for (; i != components.end(); i++)
		i->Update(input);

	UpdatePanel();
}